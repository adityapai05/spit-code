#include <iostream>
#include <string>
using namespace std;

class MusicPlaylist
{
    struct Song
    {
        int id;
        string title;
        Song *next;
    };
    Song *head;
    Song *current;

public:
    MusicPlaylist()
    {
        head = nullptr;
        current = nullptr;
    }

    void addSong(int id, string title)
    {
        Song *newSong = new Song;
        newSong->id = id;
        newSong->title = title;

        if (head == nullptr)
        {
            newSong->next = newSong;
            head = newSong;
            current = newSong;
        }
        else
        {
            Song *p = head;
            while (p->next != head)
            {
                p = p->next;
            }
            newSong->next = head;
            p->next = newSong;
        }
        cout << "\nAdded Song [" << id << " - " << title << "] to playlist.\n";
        nowPlaying();
    }

    void removeCurrentSong()
    {
        if (current == nullptr)
        {
            cout << "\nPlaylist is empty.\n";
            return;
        }

        Song *toDelete = current;
        cout << "\nRemoved Song [" << toDelete->id << " - " << toDelete->title << "].\n";

        if (head->next == head) // Only 1 song in playlist
        {
            head = nullptr;
            current = nullptr;
        }
        else
        {
            Song *prev = head;
            while (prev->next != toDelete)
            {
                prev = prev->next;
            }

            if (toDelete == head)
            {
                head = head->next;
            }
            prev->next = toDelete->next;
            current = toDelete->next;
        }

        delete toDelete;
        nowPlaying();
    }

    void nextSong()
    {
        if (current == nullptr)
        {
            cout << "\nPlaylist is empty.\n";
            return;
        }

        if (current->next == head)
        {
            cout << "\nReached end of playlist. Looping back to the first song...\n";
        }
        current = current->next;
        nowPlaying();
    }

    void nowPlaying()
    {
        if (current == nullptr)
        {
            cout << "\n[Player]: No song playing (Playlist Empty)\n";
        }
        else
        {
            cout << "\n[Now Playing]: Track #" << current->id << " - " << current->title << "\n";
        }
    }

    void displayPlaylist()
    {
        if (head == nullptr)
        {
            cout << "\nPlaylist is empty.\n";
            return;
        }

        Song *p = head;
        cout << "\nLooping Playlist:\n";
        do
        {
            if (p == current)
                cout << "[" << p->id << ":" << p->title << " (PLAYING)]";
            else
                cout << "[" << p->id << ":" << p->title << "]";
            cout << " -> ";
            p = p->next;
        } while (p != head);
        cout << "(Loops back to " << head->title << ")\n";
    }
};

int main()
{
    MusicPlaylist playlist;
    int choice, id;
    string title;

    do
    {
        cout << "\n===== MUSIC PLAYLIST LOOP =====\n";
        cout << "1. Add Song to Playlist\n";
        cout << "2. Play Next Song\n";
        cout << "3. Remove Current Song\n";
        cout << "4. Show Now Playing\n";
        cout << "5. Display Looping Playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Track ID: ";
            cin >> id;
            cout << "Enter Song Title (no spaces, e.g., Shape_Of_You): ";
            cin >> title;
            playlist.addSong(id, title);
            break;

        case 2:
            playlist.nextSong();
            break;

        case 3:
            playlist.removeCurrentSong();
            break;

        case 4:
            playlist.nowPlaying();
            break;

        case 5:
            playlist.displayPlaylist();
            break;

        case 0:
            cout << "Exiting Music Player...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}