#include "SongCollection.h"
namespace sdds {
	void printbar(std::ostream& out = std::cout)
	{
		out << std::setw(89) << std::setfill('-') << '\n'
			<< std::setfill(' ');
	}

	// String processesors:
	void trim(string& string) // quick trim
	{
		string.erase(string.find_last_not_of(' ') + 1);
		string.erase(0, string.find_first_not_of(' '));
	}

	void erase(string& stream, int n) // quick erase
	{
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
				erase(stream, 25);
				trim(title);

			artist = stream.substr(0, 25);
				erase(stream, 25);
				trim(artist);

			album = stream.substr(0, 25);
				erase(stream, 25);
				trim(album);

			year = stream.substr(0, 5);
				erase(stream, 5);
				trim(year);

			length = stream.substr(0, 5);
				erase(stream, 5);
				trim(length);

			price = stream.substr(0, 5);
				trim(price);
						
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

	void SongCollection::display(ostream& os)
	{
		total = 0;
		
		for (auto& i : songs)
		{
			os << i << '\n';
			total += i.length;
		}

		printbar(os);
		
		// Process time:
		int hrs = total / 3600;
		int mns = total / 60;
		mns -= (hrs * 60);
		int sec = total % 60;

		string time = "Total Listening Time: " + to_string(hrs) + ":" + to_string(mns) + ":" + to_string(sec);
		
		os << "|" << right << setw(85) << setfill(' ') << time << " |" << endl;
	}

	void SongCollection::sort(string str)
	{
		if (str == "title")
		{
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.title < s2.title;
				});
		}
		else if (str == "artist")
		{
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.artist < s2.artist;
				});
		}
		else if (str == "album")
		{
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.album < s2.album;
				});
		}
		else if (str == "length")
		{
			std::sort(songs.begin(), songs.end(), [](Song s1, Song s2) {
				return s1.length < s2.length;
				});
		}
	}

	void SongCollection::cleanAlbum()
	{
		for (auto& song : songs)
		{
			if (song.album == "[None]")
				song.album = "";
		}
	}

	bool SongCollection::inCollection(string str) const
	{
		bool found = false;
		for (auto& song : songs)
		{
			if (str == song.artist)
				found = true;
		}
		return found;
	}

	vector<Song> SongCollection::getSongsForArtist(string str) const
	{
		vector<Song> artist;
		for (auto& song : songs)
		{
			if (song.artist == str)
				artist.push_back(song);
		}
		return artist;
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