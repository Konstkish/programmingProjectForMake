#ifndef EMAILWORK_H
#define EMAILWORK_H

#define CURL_STATICLIB
#include <curl/curl.h>
#include <QString>
#include <string>
#include <stringswitcher.h>

struct emailWork
{

private:

    std::string _To, _From, _Subject, _Message;
    std::string eq, eq2, eq3, eq4;

    void preparePayload();

public:

emailWork(std::string Sender, std::string Subject, std::string Message);


QString getEmail(int a, std::string user, std::string pass, std::string pop3address = "localhost");


bool sendEmail(std::string reciver, std::string smtpaddress = "localhost");

};

#endif // EMAILWORK_H
