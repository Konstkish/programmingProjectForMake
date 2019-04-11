#include "emailwork.h"
#include <iostream>


emailWork::emailWork(std::string Sender, std::string Subject, std::string Message)
    :_From(Sender), _Subject(Subject), _Message(Message)
{

}

 char *payload_text[] = {
 "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
 "To: <To>\r\n",
 "From: <From>\r\n",
 "Cc:\r\n",
 "Message-ID: <Number>\r\n",
 "Subject: <Subject>\r\n",
 "\r\n", /* empty line to divide headers from body, see RFC5322 */
 "<Message>\r\n",
 "\r\n",
 "\r\n",
 "\r\n",
 nullptr
};

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

struct upload_status
{
    int lines_read;
};

size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }



  data = payload_text[upload_ctx->lines_read];

  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
  }

  return 0;
}


QString emailWork::getEmail(int a, std::string user, std::string pass, std::string pop3address)
{
    CURL *curl;

    CURLcode res = CURLE_OK;
    std::string readBuffer;
    std::string temp = "pop3://" + pop3address + "/" + QString::number(a).toStdString();


    const char* username = user.c_str();
    const char* password = pass.c_str();


    const char* url = temp.c_str();


    curl = curl_easy_init();


    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

    /* Always cleanup */
    curl_easy_cleanup(curl);
}
  QString email = QString::fromStdString(readBuffer);
return email;
}


bool emailWork::sendEmail(std::string reciver, std::string smtpaddress)
{
    _To = reciver;
    preparePayload();


    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipiants = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    std::string smtpAdd = "smtp://" + smtpaddress;

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, smtpAdd.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, reciver.c_str());

        recipiants = curl_slist_append(recipiants, _To.c_str());

        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipiants);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, &payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_preform failed: %s\n", curl_easy_strerror(res));
            return 0;
        }

        curl_slist_free_all(recipiants);

        curl_easy_cleanup(curl);
    }
    return 1;
}


void emailWork::preparePayload()
{
    std::pair<std::string, std::string> toSwitch("<To>", _To), fromSwitch("<From>", _From), subjectSwitch("<Subject>", _Subject), messageSwitch("<Message>", _Message);

    std::string _ToS = "To: <To>\r\n";
    std::string _FromS = "From: <From>\r\n";
    std::string _SubjectS = "Subject: <Subject>\r\n";
    std::string _MessageS = "<Message>\r\n";

    stringSwithcer::variadicReplacer(_ToS, toSwitch);
    stringSwithcer::variadicReplacer(_FromS, fromSwitch);
    stringSwithcer::variadicReplacer(_SubjectS, subjectSwitch);
    stringSwithcer::variadicReplacer(_MessageS, messageSwitch);

    eq = _ToS;
    eq2 = _FromS;
    eq3 = _SubjectS;
    eq4 = _MessageS;

    std::cout << _ToS << std::endl;

    payload_text[7] = const_cast<char*>(eq4.c_str());
    payload_text[1] = const_cast<char*>(eq.c_str());
    payload_text[2] = const_cast<char*>(eq2.c_str());
    payload_text[5] = const_cast<char*>(eq3.c_str());
}
