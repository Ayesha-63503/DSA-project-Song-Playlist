#include <iostream>
using namespace std;

class RecentlyPlayed {
    Song* head;
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
    cout<<"playlist";
};

