#pragma once // prevent the header from being included more than once.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <list>
using namespace std;
namespace sdds
{
	void trim(string&);
	struct Song
	{
		string artist, title, album, price, year, mins, secs;
		int length;
		double m_price;
	};
	class SongCollection
	{
		int total;
		vector<Song> songs;
	public:
		SongCollection(string);
		void display(ostream&);
		void sort(string);
		void cleanAlbum();
		bool inCollection(string) const;
		vector<Song> getSongsForArtist(string) const;
	};
	ostream& operator<<(ostream&, const Song&);
} // sdds