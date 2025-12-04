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
void addSong(const string& title, const string& artist) {
        Song* s = new Song(title, artist);
        if (!head) head = tail = s;
        else {
            tail->next = s;
            s->prev = tail;
            tail = s;
        }
        cout << "Added: " << title << endl;
    }

    void deleteSong(const string& title) {
        Song* t = head;
        while (t && t->title != title)
            t = t->next;

        if (!t) {
            cout << "Song not found." << endl;
            return;
        }

        if (t == head)
            head = t->next;

        if (t == tail)
            tail = t->prev;

        if (t->prev)
            t->prev->next = t->next;

        if (t->next)
            t->next->prev = t->prev;

        if (t == current)
            current = head;

        delete t;
        cout << "Song deleted." << endl;
    }

    void simulatePlay() {
        cout << "Playing ";
        for (int i = 0; i < 10; i++) {
            cout << "? ";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        cout << endl;
    }

    void playSong() {
        if (!head) { cout << "No songs!\n"; return; }
        if (!current) current = head;

        cout << "\nNow Playing: " << current->title << " - " << current->artist << endl;

        simulatePlay();
        recent.add(current->title, current->artist);

        if (repeatMode == 1) playSong();
        else if (current->next) current = current->next;
        else if (repeatMode == 2) current = head;
    }

    void nextSong() {
        if (!head) return;
        if (!current) current = head;
        if (current->next) current = current->next;
        else { cout << "End of playlist!\n"; return; }
        playSong();
    }