#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Reader {  
public:
    virtual ~Reader() {}
    virtual void parse(string& url) = 0;
};

class ResourceReader {
private:
    Reader* reader;
public:
    ResourceReader(Reader* r) : reader(r) {}
    ~ResourceReader() {delete reader; }

    void setStrategy(Reader* r){
    if (reader != nullptr) delete reader;
    reader = r;
    }

    void read(string& url){
    reader->parse(url);
    }
};

class Url{
public:
    string url;
    Url (string url) {
        this->url = url;
    }
    void changeUrl(string nUrl) {
        this->url = nUrl;
    }
    ~Url() {
    }

    friend std::ostream& operator<<(std::ostream& out, const Url& u) {
        out << "URL: " << u.url << endl;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Url& u) {
        cout << "Enter url: ";
        in >> u.url;
        return in;
    }
};

class NewsSiteReader : public Reader {
public:
    void parse(string& url) override {
        cout << "Parsing from site" << url << endl;
        // You can write some parse code and it will work
    } 
};

class SocialNetworkReader : public Reader {
public:
    void parse(string& url) override {
        cout << "Parsing from social network" << url << endl;
        // You can write some parse code and it will work
    } 
};

class TelegramChannelReader : public Reader {
public:
    void parse(string& url) override {
        cout << "Parsing from telegram" << url << endl;
        // You can write some parse code and it will work
    }
};

int main()
{
    ResourceReader* resourceReader = new ResourceReader(new NewsSiteReader());
    vector<string> linkCollection = vector<string>();

    Url url = Url("https://news.com");
    resourceReader->read(url.url);
    linkCollection.push_back(url.url);

    url.changeUrl("https://facebook.com");
    cin >> url; 
    resourceReader->setStrategy(new SocialNetworkReader());
    linkCollection.push_back(url.url);

    url.changeUrl("@news_channel_tg");
    resourceReader->setStrategy(new TelegramChannelReader());
    resourceReader->read(url.url);
    linkCollection.push_back(url.url);

    for(auto link : linkCollection ) {
        cout << link << " ";
    }

    int n = 4;
    int c[n];

    return 0;
}