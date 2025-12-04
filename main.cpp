// DSA Project - Song Playlist 
#include <iostream>
#include <string>
#include <vector>            // amna kashif
#include <fstream>
#include <cstdlib>                     //Ayesha Abbasi
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;        // bareera amjad 


struct Song {     //Muqaddisa Rashid
    string title;
    string artist;
    bool favorite;
    Song* next;
    Song* prev;
   

    Song(string t = "", string a = "") {          // constructor  
        title = t;
        artist = a;
        favorite = false;
        next = NULL;
        prev = NULL;
    }
};
                         //Ayesha Abbasi
class RecentlyPlayed {
    Song* head;
    int count;

public:
    RecentlyPlayed() {                    //Last 5 recent songs will be displayed
        head = NULL;
        count = 0;
    }

    void add(const string& title, const string& artist) {
        Song* s = new Song(title, artist);
        s->next = head;
        head = s;
        count++;

        if (count > 5) {
            Song* t = head;
            Song* prev = NULL;
            int c = 1;
            while (t && c < 5) {
                prev = t;
                t = t->next;
                c++;
            }
            if (prev) prev->next = NULL;
            delete t;
            count = 5;
        }
    }

    void show() {
        if (!head) {
            cout << "No songs played recently." << endl;
            return;
        }
        cout << "Recently Played:" << endl;
        Song* t = head;
        int i = 1;
        while (t) {
            cout << i << ". " << t->title << " - " << t->artist << endl;
            t = t->next;
            i++;
        }
    }
};

class Playlist {
    string name;
    Song* head;
    Song* tail;
    Song* current;
    int repeatMode; // 0 = Off, 1 = Repeat One, 2 = Repeat All
    RecentlyPlayed recent;

public:
    Playlist(string n = "My Playlist") { //constructor
        name = n;
        head = tail = current = NULL;
        repeatMode = 0;
    }

    string getName() {
        return name;
    }