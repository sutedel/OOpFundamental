// Name: Ahmad Jafari
// ID: 143469195
// Date of completion: 07/16/2021
//
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds {
	class Station
	{
		int m_stationId;
		std::string m_itemName;
		std::string m_description;
		unsigned int m_nextItem;
		unsigned int m_stock;
		static unsigned int m_widthField;
		static unsigned int m_idGenerator;
	public:
		Station();
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full)const;


	};
}
#endif