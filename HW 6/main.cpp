#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message) {
    cout << "Send '" << message << "' to number " << number << endl;
}
void SendEmail(const string& email, const string& message) {
    cout << "Send '" << message << "' to e-mail " << email << endl;
}

class INotifier {
public:
    virtual void Notify(const std::string& message) const = 0;
};

class SmsNotifier : public INotifier {
private:
    std::string phoneNumber;
public:
    SmsNotifier(const std::string& number) : phoneNumber(number) {}
    void Notify(const std::string& message) const override {
        SendSms(phoneNumber, message);
    }
};

class EmailNotifier : public INotifier {
private:
    std::string emailAddress;
public:
    EmailNotifier(const std::string& email) : emailAddress(email) {}
    void Notify(const std::string& message) const override {
        SendEmail(emailAddress, message);
    }
};

int main() {
    SmsNotifier sms { " + 7-923-228-38-72 " };
    EmailNotifier email { " m.Filippov@g.nsu.ru " };
    sms.Notify("I know lessons in C++'");
    email.Notify("And want the lesson one ");
    return 0;
}

