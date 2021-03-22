#include "SongCollection.h"
namespace sdds {
	void printbar(std::ostream& out = std::cout)
	{
		out << std::setw(89) << std::setfill('-') << '\n'
			<< std::setfill(' ');
	}

	// Quick-Trim: Overloaded function that processes strings.
	void qtrim(string& str)
	{
		str.erase(str.find_last_not_of(' ') + 1);
		str.erase(0, str.find_first_not_of(' '));
	}

	void qtrim(string& str, string& stream, int n)
	{
		str.erase(str.find_last_not_of(' ') + 1);
		str.erase(0, str.find_first_not_of(' '));
		stream.erase(0, n);
	}

	SongCollection::SongCollection(string filename)
	{
		total = 0;
		fstream file(filename);
		while (file)
		{
			// Declare strings to set, a new Song and set stream:
			string stream, title, artist, album, year, length, price;
			Song newSong;
			getline(file, stream, '\n');
			
			// Get string from stream, erase and then trim string:
			title = stream.substr(0, 25);
			qtrim(title, stream, 25);

			artist = stream.substr(0, 25);
			qtrim(artist, stream, 25);

			album = stream.substr(0, 25);
			qtrim(album, stream, 25);

			year = stream.substr(0, 5);
			qtrim(year, stream, 5);

			length = stream.substr(0, 5);
			qtrim(length, stream, 5);

			price = stream.substr(0, 5);
			qtrim(price);
						
			// Process length using stringstream:
			stringstream streamLength(length);
			streamLength >> newSong.length;
			// Set min and sec variables
			int min = newSong.length / 60;	// calculate minutes
			int sec = newSong.length % 60;	// calculate seconds

			// Process price using stringstream:
			stringstream priceStream(price);
			priceStream >> newSong.m_price;

			// Set processed strings to song object.
			newSong.title = title;
			newSong.artist = artist;
			newSong.album = album;
			newSong.year = year;
			newSong.mins = to_string(min);
			newSong.secs = to_string(sec);
			newSong.price = price;
			
			// New Song is complete, push into 'songs'
			songs.push_back(newSong);
		}
		songs.pop_back();
	}

	void SongCollection::display(ostream& out) const {
		for_each(songs.begin(), songs.end(), [&out](const Song
			& song) {
				out << song << endl;
			});
	}

	void SongCollection::sort(string str)
	{
		if (str == "title")	{
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.title < s2.title;
				});
		}
		else if (str == "artist") {
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.artist < s2.artist;
				});
		}
		else if (str == "album") {
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.album < s2.album;
				});
		}
		else if (str == "length") {
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.length < s2.length;
				});
		}
	}

	void SongCollection::cleanAlbum()
	{
		for_each(songs.begin(), songs.end(), [](Song& song) { song.album = song.album == "[None]" ? "" : song.album; });
	}

	bool SongCollection::inCollection(string str) const
	{
		auto valid = find_if(songs.begin(), songs.end(),
			[&str](const Song& song) {return song.artist == str; });
		return valid != songs.end();

	}

	::list<Song> SongCollection::getSongsForArtist(string artist) const {
		auto count = count_if(songs.begin(), songs.end(),
			[&artist](const Song& song) {
				return song.artist == artist;
			});

		list<Song>listed(count);
		copy_if(songs.begin(), songs.end(), listed.begin(),
			[&artist](const Song& song) {
				return song.artist == artist;
			});
		return listed;
	}
	
	ostream& operator<<(ostream& os, const Song& song)
	{
		os << "| ";
		os << left << setw(20) << song.title << " | ";
		os << left << setw(15) << song.artist << " | ";
		os << left << setw(20) << song.album << " | ";
		os << right << setw(6) << song.year << " | ";
		os << song.mins << ":";
		os << setw(2) << setfill('0') << song.secs << setfill(' ') << " | ";
		os << song.m_price << " |";
		return os;
	}
} // sdds