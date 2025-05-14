#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;

enum SeatStatus { AVAILABLE, BOOKED };

class Seat {
public:
    int row;
    int number;
    SeatStatus status;

    Seat(int r, int n) : row(r), number(n), status(AVAILABLE) {}

    bool isAvailable() const {
        return status == AVAILABLE;
    }

    void book() {
        status = BOOKED;
    }

    void cancel() {
        status = AVAILABLE;
    }
};

class Movie {
public:
    string title;
    int duration; // in minutes

    Movie(string t, int d) : title(t), duration(d) {}
};

class Show {
public:
    string startTime;
    Movie movie;
    vector<Seat> seats;
    int showId;

    Show(int id, string time, Movie m, int totalSeats)
        : showId(id), startTime(time), movie(m) {
        for (int i = 0; i < totalSeats; i++) {
            seats.emplace_back(0, i + 1);
        }
    }

    vector<int> getAvailableSeats() {
        vector<int> result;
        for (auto& seat : seats) {
            if (seat.isAvailable()) {
                result.push_back(seat.number);
            }
        }
        return result;
    }

    bool bookSeat(int seatNum) {
        if (seatNum <= 0 || seatNum > seats.size()) return false;
        if (seats[seatNum - 1].isAvailable()) {
            seats[seatNum - 1].book();
            return true;
        }
        return false;
    }

    void cancelSeat(int seatNum) {
        if (seatNum <= 0 || seatNum > seats.size()) return;
        seats[seatNum - 1].cancel();
    }
};

class Screen {
public:
    int screenId;
    vector<Show> shows;

    Screen(int id) : screenId(id) {}

    void addShow(Show s) {
        shows.push_back(s);
    }
};

class Theatre {
public:
    int theatreId;
    string name;
    string city;
    vector<Screen> screens;

    Theatre(int id, string n, string c) : theatreId(id), name(n), city(c) {}

    void addScreen(Screen s) {
        screens.push_back(s);
    }
};

class Booking {
public:
    int bookingId;
    int showId;
    int seatNumber;

    Booking(int id, int sid, int snum)
        : bookingId(id), showId(sid), seatNumber(snum) {}
};

class User {
public:
    string name;
    vector<Booking> bookings;

    User(string n) : name(n) {}

    void bookTicket(Show& show, int seatNum, int bookingId) {
        if (show.bookSeat(seatNum)) {
            bookings.emplace_back(bookingId, show.showId, seatNum);
            cout << "Booking successful for " << name << endl;
        } else {
            cout << "Seat already booked.\n";
        }
    }

    void cancelTicket(Show& show, int bookingId) {
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if (it->bookingId == bookingId) {
                show.cancelSeat(it->seatNumber);
                bookings.erase(it);
                cout << "Booking cancelled for " << name << endl;
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }
};

class BookingSystem {
public:
    vector<Theatre> theatres;
    int bookingCounter = 1;

    void addTheatre(Theatre t) {
        theatres.push_back(t);
    }

    vector<Movie> searchMoviesByCity(string city) {
        map<string, bool> seen;
        vector<Movie> result;
        for (auto& theatre : theatres) {
            if (theatre.city == city) {
                for (auto& screen : theatre.screens) {
                    for (auto& show : screen.shows) {
                        if (!seen[show.movie.title]) {
                            result.push_back(show.movie);
                            seen[show.movie.title] = true;
                        }
                    }
                }
            }
        }
        return result;
    }

    Show* findShowById(int id) {
        for (auto& theatre : theatres) {
            for (auto& screen : theatre.screens) {
                for (auto& show : screen.shows) {
                    if (show.showId == id) return &show;
                }
            }
        }
        return nullptr;
    }

    void book(User& user, int showId, int seatNum) {
        Show* show = findShowById(showId);
        if (show) {
            user.bookTicket(*show, seatNum, bookingCounter++);
        } else {
            cout << "Show not found.\n";
        }
    }

    void cancel(User& user, int bookingId, int showId) {
        Show* show = findShowById(showId);
        if (show) {
            user.cancelTicket(*show, bookingId);
        }
    }
};
