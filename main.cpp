// DSA Project - Song Playlist 

#include <iostream>
#include <string>
#include <vector>            
#include <fstream>
#include <cstdlib>                     //Ayesha Abbasi
#include <ctime>

using namespace std;
class RecentlyPlayed {
    Song* head;             //Bareera Amjad
    int count;

public:
    RecentlyPlayed() {
        head = nullptr;
        count = 0;
    }

    void addRecent(string title, string artist) {
        Song* song = new Song(title, artist);
        song->next = head;
        head = song;
        count++;

        if (count > 5) {
            Song* temp = head;
            Song* prev = nullptr;
            int c = 1;
            while (temp && c < 5) {
                prev = temp;
                temp = temp->next;
                c++;
            }
            if (temp && prev) {
                prev->next = nullptr;
                delete temp;
                count = 5;
            }
        }
    }

    void showRecent() {
        if (head == nullptr) {
            cout << endl << "No songs have been played recently!" << endl;
            return;
        }

        cout << endl << "Recently Played Songs:" << endl;
        Song* current = head;
        int index = 1;

        while (current != nullptr) {
            cout << index++ << "." << current->title << "—" << current->artist << endl;
            current = current->next;
        }
    }
};
 void simulatePlay() {
    cout << "Playing ";
    for (int i = 0; i < 10; i++) {
        cout << "? ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200)); // small delay to simulate playback
    }
    cout << endl;
}

void playSong() {                                                                               //Ayesha Abbasi
    if (!head) { cout << "No songs!\n"; return; } // check if playlist is empty
    if (!current) current = head; // start from first song if none select
                 
    // Display current song info
    cout << "\n?? Now Playing: " << current->title << " - " << current->artist;
    if (current->favorite) cout << " ?️";
    cout << endl;

    simulatePlay(); // simulate playback animation
    recent.addRecent(current->title, current->artist); // add song to recent list

    // Handle repeat and auto-next logic
    if (repeatMode == 1) playSong(); // repeat current
    else if (current->next) current = current->next; // go to next
    else if (repeatMode == 2) current = head; // loop to start
}

void nextSong() {
    if (!head) return;
    if (!current) current = head;
    if (current->next) current = current->next;
    else { cout << "End of playlist!\n"; return; } // no next song
    playSong(); // play next
}

void prevSong() {
    if (!head) return;
    if (!current) current = head;
    if (current->prev) current = current->prev;
    else { cout << "Start of playlist!\n"; return; } // no previous song
    playSong(); // play previous
}
// Amna Kashif
class Song {
public:
    string title;
    string artist;
    Song* next;
    Song* prev;

    Song(const string& t, const string& a) {
        title = t;
        artist = a;
        next = nullptr;
        prev = nullptr;
    }
};

class PlayList{
private:
	Song*head;
	Song*tail;
	

public:
	PlayList(){
		head=nullptr;
		tail=nullptr;
	}
// changing
void addSong(const string& artist,const string& title)	{
	Song*newSong=new Song(title,artist){
		if(head==nullptr){
			head=tail=newSong;
		}else{
			tail->next=newSong;
			newSong->prev=tail;
			tail=newSong;
		}
		cout<<"SongAdded:"<<title<<"by"<<Artist<<endl;
	}
}
void deleteSong(const string& title) {
        if (head == nullptr) {
            cout << "Playlist is empty!"<<endl;
            return;
        }

        Song* temp = head;

        while (temp != nullptr && temp->title != title) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Song not found!"<<endl;
            return;
        }


        if (temp == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
            else tail = nullptr; 
        }
        
        else if (temp == tail) {
            tail = tail->prev;
            if (tail != nullptr) tail->next = nullptr;
            else head = nullptr; 
        }
        
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Song deleted: " << title <<endl;
    }
    // changing 
    void displayForward() const {
        if (head == nullptr) {
            cout << "Playlist is empty!"<<endl;
            return;
        }

        cout << "Playlist (Forward):"<<endl;
        Song* temp = head;
        while (temp != nullptr) {
            cout << "Title: " << temp->title << " | Artist: " << temp->artist <<endl;
            temp = temp->next;
        }
    }

    void displayBackward() const {
        if (tail == nullptr) {
            cout << "Playlist is empty!"<<endl;
            return;
        }

        cout << "Playlist (Backward):"<<endl;
        Song* temp = tail;
        while (temp != nullptr) {
            cout << "Title: " << temp->title << " | Artist: " << temp->artist <<endl;
            temp = temp->prev;
        }
    }
    
    ~Playlist() {
        Song* temp = head;
        while (temp != nullptr) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};
//main function
#include "Playlist.h"

int main() {
    Playlist myPlaylist;
    int choice;
    string title, artist;

    do {
        cout << " SONG PLAYLIST MENU "<<endl;
        cout << "1. Add Song"<<endl;
        cout << "2. Delete Song"<<endl;
        cout << "3. Display Playlist (Forward)"<<endl;
        cout << "4. Display Playlist (Backward)"<<endl;
        cout << "5. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            getline(cin, title);
            cout << "Enter artist name: ";
            getline(cin, artist);
            myPlaylist.addSong(title, artist);
            break;

        case 2:
            cout << "Enter song title to delete: ";
            getline(cin, title);
            myPlaylist.deleteSong(title);
            break;

        case 3:
            myPlaylist.displayForward();
            break;

        case 4:
            myPlaylist.displayBackward();
            break;

        case 5:
            cout << "🎧 Exiting Playlist Simulation. Bye!"<<endl;
            break;

        default:
            cout << "Invalid choice! Try again."<<endl;
        }

    } while (choice != 5);

    return 0;
}


	Song(const title& t,const artist& a)
};
void shuffleSongs() {
    vector<Song*> list;
    Song* temp = head;

    while (temp != NULL) {
        list.push_back(temp);
        temp = temp->next;
    }

    srand(time(0));
    for (int i = 0; i < list.size(); i++) {
        int r = rand() % list.size();
        swap(list[i]->title, list[r]->title);
        swap(list[i]->artist, list[r]->artist);
        swap(list[i]->favorite, list[r]->favorite);
    }

    cout << "Playlist shuffled!" << endl;
}
<<<<<<< HEAD
void setRepeatMode() {   //bareera amjad
    int choice;
    cout << "Choose repeat mode:" << endl;
    cout << "1. Repeat One" << endl;
    cout << "2. Repeat All" << endl;
    cout << "3. Off" << endl;
    cout << "Enter your choice (1-3): " << endl;
    cin >> choice;

    if (choice == 1) {
        repeatMode = 1;
        cout << "Repeat mode set to: One" << endl;
    } 
    else if (choice == 2) {
        repeatMode = 2;
        cout << "Repeat mode set to: All" << endl;
    } 
    else {
        repeatMode = 0;
        cout << "Repeat mode turned Off" << endl;
    }
}

=======
>>>>>>> 08c8799627eccce0fd6eaf7f4c2f53aca43160cc
