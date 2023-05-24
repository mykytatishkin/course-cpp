#include <iostream>
#include <string>
#include <map>
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
    int id;
    string url;
    Url (int nId,string url) {
        this->id = id;
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

    Url& operator++() {
        ++id;
        return *this;
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
    map<int, string> linkCollection = map<int, string>();

    Url url = Url(1,"https://news.com");
    resourceReader->read(url.url);
    linkCollection.insert(pair<int, string>(url.id, url.url));

    url.changeUrl("https://facebook.com");
    cin >> url;
    url.id++;

    resourceReader->setStrategy(new SocialNetworkReader());
    linkCollection.insert(pair<int, string>(url.id, url.url));

    url.changeUrl("@news_channel_tg");
    url.id++;

    resourceReader->setStrategy(new TelegramChannelReader());
    resourceReader->read(url.url);
    linkCollection.insert(pair<int, string>(url.id, url.url));

    std::map<int, string>::iterator it = linkCollection.begin();
 
    // Iterate through the map and print the elements
    while (it != linkCollection.end())
    {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        ++it;
    }

    return 0;
}