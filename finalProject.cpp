#include <bits/stdc++.h>
using namespace std;

struct dt
{
    int day;
    int month;
    int year;
};


class users
{
private:
    int Indicator = 100;
    string name, bio;
    int picId, nuPhoto, activityTime, nuFollower, nuComment, nuMessage, nuReport;
    bool govtId;
    vector<string> comments;
    vector<string> messages;
    vector<int> pastComment;
    vector<int> pastMessages;
    vector<int> listPhoto;
    vector<int> countPost;
    struct dt date;
    // struct tms time;//delete

public:
    bool any_nameMatched = 0, any_govt = 0, any_scamMessage = 0, any_postMatching = 0, any_activityTime = 0, any_freqPosting = 0, any_freqCommenting = 0, any_report = 0, any_bioMatched = 0;
    vector<string> split(string, char);
    string lower_string(string);
    bool calcPercentage(users &);
    void check_msg_cmt(vector<string>);
    void freq_of_post();
    void checkCount(int, int, users &);
    void checkPhotos(bool, users &);
    string checkName(string, map<string, string> &, int &);
    void checkGovt();
    void func(users &, map<string, string> &);
    void actTime();
    void reportTest();
    void set(string name, string bio, int picId, int nuPhoto, int activityTime, int nuFollower, int nuComment, int nuMessage, int nuReport, bool govtId, vector<string> comments,
             vector<string> messages, vector<int> pastComment, vector<int> pastMessage, struct dt Date, vector<int> listPhoto, vector<int> countpost)
    {
        this->name = name;
        this->bio = bio;
        this->picId = picId;
        this->nuPhoto = nuPhoto;
        this->activityTime = activityTime;
        this->nuFollower = nuFollower;
        this->nuComment = nuComment;
        this->nuMessage = nuMessage;
        this->nuReport = nuReport;
        this->govtId = govtId;
        this->comments = comments;
        this->messages = messages;
        this->pastComment = pastComment;
        this->pastMessages = pastMessage;
        (this->date).day = Date.day;
        (this->date).month = Date.month;
        (this->date).year = Date.year;
        this->listPhoto = listPhoto;
        this->countPost = countPost;
        //(this->time).hour = Time.hour;
        //(this->time).min = Time.min;
    }
    string getname() { return name; }
    string getbio() { return bio; }
    int getpicId() { return picId; }
    int getnuPhoto() { return nuPhoto; }
    int getactivityTime() { return activityTime; }
    int getnuFollower() { return nuFollower; }
    int getnuComment() { return nuComment; }
    int getnuMessage() { return nuMessage; }
    int getnuReport() { return nuReport; }
    bool getgovtId() { return govtId; }
    vector<string> getcomments() { return comments; }
    vector<string> getmessages() { return messages; }
    vector<int> getpastComment() { return pastComment; }
    vector<int> getpastMessages() { return pastMessages; }
    struct dt getdate() { return date; }
    // struct tms gettime(){return time};
    void print();
    void set_indicator(int indi, bool x)
    {
        if (x)
            Indicator += indi;
        else
            Indicator -= indi;
        if (Indicator > 100)
            Indicator = 100;
        if (Indicator < 0)
            Indicator = 0;
    }
    vector<int> getcountPost() { return countPost; }
    vector<int> getlistPhoto() { return listPhoto; }
    void print_result()
    {
        cout << name << endl;
        if (any_nameMatched)
            cout << "NAME MATCHED" << endl;
        else
            cout << "NAME NOT MATCHED" << endl;
        if (any_scamMessage)
            cout << "SCAM MESSAGE DETECTED" << endl;
        else
            cout << "NO SCAM MESSAGE FOUND" << endl;
        if (any_postMatching)
            cout << "POST MATCH FOUND" << endl;
        else
            cout << "NO POSTS MATCHED" << endl;
        if (any_freqCommenting)
            cout << "FREQUENT COMMENTS FOUND" << endl;
        else
            cout << "NO FREQUENT COMMENTS FOUND" << endl;
        if (any_activityTime)
            cout << "LOW ACTIVITY TIME FOUND" << endl;
        else
            cout << "ACTIVITY TIME IS GOOD" << endl;
        if (any_bioMatched)
            cout << "BIO IS MATCHED" << endl;
        else
            cout << "BIO IS NOT MATCHED " << endl;
        if (any_report)
            cout << "REPORTS FOUND" << endl;
        else
            cout << "NO REPORTS FOUND" << endl;
        if (any_govt)
            cout << "ACCOUNT VERIFIED " << endl;
        else
            cout << "ACCOUNT NOT VERIFIED" << endl;
        cout << "AUTHENTICITY PERCENTAGE: " << Indicator << " %" << endl;

        cout << endl
             << endl
             << endl;
    }
};
//**********************print*********************************
void users::print()
{
    cout << name << endl
         << bio << endl
         << picId << endl
         << nuPhoto << endl
         << activityTime << endl
         << nuFollower << endl
         << nuComment << endl
         << date.day << endl
         << date.month << endl
         << date.year << endl;
    for (int i = 0; i < listPhoto.size(); i++)
        cout << listPhoto[i] << endl;
    for (int i = 0; i < messages.size(); i++)
        cout << messages[i] << endl;
}

//******************** 4 ) CHECK MESSAGE*******************************
void users ::check_msg_cmt(vector<string> fake)
{ //
    int count_fake_phrase = 0;
    vector<string> msg = getmessages();
    for (int i = 0; i < msg.size(); i++)
    {
        msg[i] = lower_string(msg[i]);
    }
    vector<string> cmt = getcomments();
    for (int i = 0; i < cmt.size(); i++)
        cmt[i] = lower_string(cmt[i]);
    int sent_cmt = 0;
    int sent_msg = 0;
    vector<int> temp_cmnt = getpastComment();
    vector<int> temp_msg = getpastMessages();
    for (int i = 0; i < temp_cmnt.size(); i++)
        sent_cmt += temp_cmnt[i];
    for (int i = 0; i < temp_msg.size(); i++)
        sent_msg += temp_msg[i];
    for (int j = 0; j < msg.size(); j++)
        for (int i = 0; i < fake.size(); i++)
        {
            if (msg[j].find(fake[i]) != string::npos)
            {
                count_fake_phrase++;
            }
        }
    for (int j = 0; j < cmt.size(); j++)
        for (int i = 0; i < fake.size(); i++)
        {
            if (cmt[j].find(fake[i]) != string::npos)
            {
                count_fake_phrase++;
            }
        }
    if (count_fake_phrase >= 3 && (sent_msg > 10 || sent_cmt > 10))
    {
        set_indicator(30, 0);
        any_scamMessage = 1;
    }
    else if (count_fake_phrase >= 3)
    {
        any_scamMessage = 1;
        set_indicator(15, 0);
    }
}
//********************CHECK MESSAGE OVER*****************************

//******************** 5 ) FREQUENCY OF POSTING AND CHECKING REPORTS*********************
void users ::freq_of_post()
{
    vector<int> comment = getpastComment();
    vector<int> post = getcountPost();
    int weekpost = 0;
    int indicator = 0;
    for (int i = 0; i < comment.size(); i++)
    {
        if (comment[i] > 400)
        {
            any_freqCommenting = 1;
            indicator = max(indicator, 25);
        }

        else if (comment[i] > 300)
        {
            any_freqCommenting = 1;
            indicator = max(indicator, 20);
        }
        else if (comment[i] > 200)
        {

            any_freqCommenting = 1;
            indicator = max(indicator, 15);
        }
        else if (comment[i] > 100)
        {
            any_freqCommenting = 1;
            indicator = max(indicator, 10);
        }

        else if (comment[i] > 50)
        {
            any_freqCommenting = 1;
            indicator = max(indicator, 5);
        }
    }

    set_indicator(indicator, 0);
}
//********************FREQUENCY OF POSTING AND CHECKING REPORTS OVER*********************

//******************* 6 ) CHECKING IF PHOTOS IS SIMILAR CHECKING BIO CHECKING PROFILE*********************


//********************** 1 ) Bio******************************

// Splitting all the words in the vector
vector<string> users ::split(string str, char delimiter)
{
    vector<string> v1;
    string temp;
    for (char c : str)
    {
        if (c == delimiter)
        {
            v1.push_back(temp);
            temp.clear();
        }
        else
        {
            temp += c;
        }
    }
    // here we return the vector
    v1.push_back(temp);
    return v1;
}
//*************** 2 ) Lower Case ****************************
// Case Insensitive
string users ::lower_string(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') // checking for uppercase characters
            str[i] = str[i] + 32;           // converting uppercase to lowercase
    }
    return str;
}

//******************* 3 ) Calculate Percentage  ***********************

bool users ::calcPercentage(users &usr)
{
    string s1 = usr.getbio();
    string s2 = getbio();
    vector<string> words1 = split(lower_string(s1), ' ');
    vector<string> words2 = split(lower_string(s2), ' ');
    int count = 0;
    int len1 = words1.size();
    int len2 = words2.size();
    // Comparision of all the words
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            if (words1[i] == words2[j])
            {
                count++;
                break;
            }
        }
    }
    float percentage = (float)count / (float)(len1 + len2) * 100.0;
    // Check if Percentage is greater than 80% then it will set bio matched value with 1
    if (percentage > 80)
    {
        any_bioMatched = 1;
        return true;
    }
    return false;
}
//********************BIO------END*****************************


// For checking Count of How many Images are similar
// there are 2 cases arrive in this
// count = 4 and profile pic also matches

void users ::checkCount(int sameProfile, int count, users &usr)
{
    struct dt passed_d = usr.getdate();
    int indicator = 0;
    struct dt caller_d = getdate();
    if ((sameProfile && count > 0) || calcPercentage(usr))
    {

        indicator = 50;
    }
    else if (count > 0)
    {
        indicator = 30;
    }
    if (passed_d.month > caller_d.month || (passed_d.month == caller_d.month && passed_d.day > caller_d.day))
    {
        usr.any_nameMatched = 1;
        usr.set_indicator(indicator, 0);
        usr.any_postMatching = 1;
        usr.any_bioMatched = 1;
    }
    else
    {
        any_nameMatched = 1;
        any_postMatching = 1;
        any_bioMatched = 1;
        set_indicator(indicator, 0);
    }
}
//**************** 7) Checking Photots ******************
void users ::checkPhotos(bool nameRes, users &usr)
{
    if (nameRes)
    {
        int totPhoto1 = getnuPhoto();
        int totPhoto2 = usr.getnuPhoto();
        int postOf1 = getpicId();
        int postOf2 = usr.getpicId();

        bool sameProfile = 0;
        if (postOf1 == postOf2)
        {
            sameProfile = 1;
        }

        vector<int> _photos = usr.getlistPhoto();
        int count = 0;
        for (int i = 0; i < totPhoto1; i++)
        {
            for (int j = 0; j < totPhoto2; j++)
            {
                if (_photos[i] == listPhoto[j])
                {
                    count++;
                }
            }
        }
        checkCount(sameProfile, count, usr);
    }
    return;
}

//*********************** 8) Check Name ***************************
string users ::checkName(string fakestr1, map<string, string> &m1, int &j)
{
    string temp = "";

    for (auto it : m1)
    {
        size_t found = fakestr1.find(it.first);
        if (found != string::npos)
        {
            fakestr1.erase(fakestr1.find(it.first), it.first.length() - 1);
            for (int i = 0; i < fakestr1.length(); i++, j++)
            {
                if (i == found)
                {
                    temp += it.second;
                    j += it.first.length();
                    return temp;
                }
                else
                {
                    temp += fakestr1[i];
                }
            }
        }
    }
    j += fakestr1.length();
    return fakestr1;
}

//**********************MAin Function Part******************
void users::func(users &user, map<string, string> &m1)
{
    string fakestr1 = lower_string(user.getname());
    string realName = lower_string(getname());
    bool nameRes = 0;

    if (fakestr1 == realName)
    {
        nameRes = 1;
        checkPhotos(nameRes, user);
    }
    else
    {
        int n = fakestr1.length();
        int j = 0;
        string temp = "";
        nameRes = 0;
        while (j < n)
        {
            temp = temp + checkName(fakestr1.substr(j, n - j), m1, j);
        }
        if (temp == realName)
        {

            nameRes = 1;
            checkPhotos(nameRes, user);
        }
        else
        {
            string realstr1 = getname();
            int n = realstr1.length();
            int j = 0;
            string temp = "";
            while (j < n)
            {
                temp = temp + checkName(realstr1.substr(j, n - j), m1, j);
            }
            if (temp == fakestr1)
            {

                nameRes = 1;
                checkPhotos(nameRes, user);
            }
            return;
        }
    }
}

//*******************CHECKING IF PHOTOS IS SIMILAR CHECKING BIO CHECKING PROFILE OVER*********************

//**************** 9 ) CHECK GOVERMENT ID **************************************

void users ::checkGovt()
{
    if (getgovtId() == 1)
    {
        set_indicator(100, 1);
        any_govt = 1;
    }
}

void users::actTime()
{
    int atime = getactivityTime();

    if (atime < 1)
    {
        any_activityTime = 1;
        set_indicator(30, 0);
    }
    else if (atime < 5)
    {
        any_activityTime = 1;
        set_indicator(15, 0);
    }
}
void users::reportTest()
{
    int report = getnuReport();
    if (report > 100)
    {
        set_indicator(30, 0);
        // manual check
        any_report = 1;
    }
    else if (report > 50)
    {
        set_indicator(15, 0);
        any_report = 1;
    }
}
int main()
{

    vector<string> fake;
    fake.push_back("jackpot!");
    fake.push_back("act fast");
    fake.push_back("no collateral required");
    fake.push_back("lottery won!");
    fake.push_back("free money");
    fake.push_back("get rich quickly");
    fake.push_back("click the link");
    fake.push_back("we are from your bank");
    fake.push_back("your computer has a virus");
    fake.push_back("we have detected fraud in your account");
    string name, bio;
    int picId, nuPhoto, activityTime, nuMessage, nuReport;
    int nuFollower, nuComment;
    bool govtId;
    vector<string> comments;
    vector<string> messages;
    vector<int> Time, Date;
    vector<int> pastComment, pastMessage, cntPost, lspic;
    struct dt date;
    string cmnts, msgs, pstcmnt, pstmsg, d, tm, listpic, cntpost;
    users user[8];

    map<string, string> m1;

    m1["i"] = "ee";
    m1["nn"] = "n";
    m1["n"] = "nn";
    m1["li"] = "le";
    m1["ci"] = "se";
    m1["zz"] = "z";
    m1["w"] = "v";
    m1["ya"] = "a";
    m1["hr"] = "r";
    m1["v"] = "o";
    m1["t"] = "th";
    m1["@"] = "asid";

    ifstream inputFile("Database.txt");
    if (!inputFile)
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    for (int i = 0; i < 10; i++)
    {
        string line;
        getline(inputFile, line);

        size_t pos = 0;
        string token;
        int field = 0;

        while ((pos = line.find(",")) != string::npos)
        {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);

            switch (field)
            {
            case 0:
            {
                name = token;
                break;
            }
            case 1:
            {
                bio = token;
                break;
            }
            case 2:
            {
                picId = stoi(token);
                break;
            }
            case 3:
            {
                nuPhoto = stoi(token);
                break;
            }
            case 4:
            {
                activityTime = stoi(token);
                break;
            }
            case 5:
            {
                nuFollower = stoi(token);
                break;
            }
            case 6:
            {
                nuComment = stoi(token);
                break;
            }
            case 7:
            {
                nuMessage = stoi(token);
                break;
            }
            case 8:
            {
                nuReport = stoi(token);
                break;
            }

            case 9:
            {
                govtId = stoi(token);
                break;
            }
            case 10:
            {
                cmnts = token;
                string tt;
                std::stringstream ss(cmnts);
                while (std::getline(ss, tt, '_'))
                {
                    comments.push_back(tt);
                }
                break;
            }
            case 11:
            {
                msgs = token;
                string tt;
                std::stringstream ss(msgs);
                while (std::getline(ss, tt, '_'))
                {
                    messages.push_back(tt);
                }
                break;
            }
            case 12:
            {
                pstcmnt = token;
                std::stringstream ss(pstcmnt);

                // Extract phrases using getline() function
                std::string phrase;
                while (std::getline(ss, phrase, '_'))
                {
                    pastComment.push_back(stoi(phrase));
                }
                break;
            }

            case 13:
            {
                pstmsg = token;
                std::stringstream ss(pstmsg);

                // Extract phrases using getline() function
                std::string phrase;
                while (std::getline(ss, phrase, '_'))
                {
                    pastMessage.push_back(stoi(phrase));
                }
                break;
            }
            case 14:
            {
                d = token;
                std::stringstream ss(d);
                string tt;
                while (std::getline(ss, tt, '_'))
                {
                    Date.push_back(stoi(tt));
                }
                date.day = Date[0];
                date.month = Date[1];
                date.year = Date[2];
                break;
            }
            case 15:
            {
                listpic = token;
                std::stringstream ss(listpic);

                // Extract phrases using getline() function
                std::string phrase;
                while (std::getline(ss, phrase, '_'))
                {
                    lspic.push_back(stoi(phrase));
                }
                break;
            }
            case 16:
            {
                cntpost = token;
                std::stringstream ss(cntpost);

                // Extract phrases using getline() function
                std::string phrase;
                while (std::getline(ss, phrase, '_'))
                {
                    cntPost.push_back(stoi(phrase));
                }
                break;
            }
            }
            user[i].set(name, bio, picId, nuPhoto, activityTime, nuFollower, nuComment, nuMessage, nuReport, govtId, comments,
                        messages, pastComment, pastMessage, date, lspic, cntPost);

            field++;
            if (field == 16)
            {
                cntpost = token;
                std::stringstream ss(cntpost);

                // Extract phrases using getline() function
                std::string phrase;
                while (std::getline(ss, phrase, '_'))
                {
                    cntPost.push_back(stoi(phrase));
                }
            }
        }
        cntPost.clear();
        lspic.clear();
        pastComment.clear();
        pastMessage.clear();
        messages.clear();
        comments.clear();
    }
    inputFile.close();
    for (int i = 0; i < 7; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            user[i].func(user[j], m1);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        
        user[i].check_msg_cmt(fake);
        user[i].actTime();
        user[i].freq_of_post();
        user[i].reportTest();
        user[i].checkGovt();
    }
    for (int i = 0; i < 8; i++)
    {
        user[i].print_result();
    }
    return 0;
}