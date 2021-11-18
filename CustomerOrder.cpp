// Name: Ahmad Jafari
// Seneca Student ID:143469195
// Seneca email: mjafari22@myseneca.ca
// Date of completion:26/07/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignment.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
using namespace std;

namespace sdds
{
    size_t CustomerOrder::m_widthField = 1; //static definition

    //initializing all properties of CustomerOrder to empty state
    CustomerOrder::CustomerOrder()
    {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    }
    CustomerOrder::CustomerOrder(std::string& record)
    {
        Utilities temp; //temporary Utilities object
        vector<Item*> items; //for populating **
        // Set defaults for the next_pos and more
        bool flag = true;
        size_t index = 0u;
        try {
            m_name = temp.extractToken(record, index, flag);
            if (flag == true)
                m_product = temp.extractToken(record, index, flag);
            while (flag == true) //populates all the items in the items container
                items.push_back(new Item(temp.extractToken(record, index, flag)));
            m_widthField = temp.getFieldWidth(); //for the field width
            m_cntItem = static_cast<unsigned int>(items.size()); //for allocating dynamic memory purposes
            m_lstItem = new Item * [m_cntItem];

            for (size_t i = 0u; i < m_cntItem; i++)
                m_lstItem[i] = std::move(items[i]); //moving all items to the original pointer
        }
        catch (std::string ex) {
            std::cout << ex;
        }


    }
    CustomerOrder::CustomerOrder(const CustomerOrder& src)
    {
        throw std::string("Copy not permitted");
    }
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
    {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator = (CustomerOrder&& src) noexcept
    {
        if (this != &src)
        {
            m_name = src.m_name;
            m_product = src.m_product;
            m_widthField = src.m_widthField;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_name = "";
            src.m_product = "";
            src.m_widthField = 0;
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }

        return *this;
    }
    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0u; i < m_cntItem; i++)
            delete m_lstItem[i];
        delete[] m_lstItem;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {

        for (size_t i = 0u; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName())  //checks if station is matched
            {
                if (station.getQuantity() > 0)  //if station found & inventory has at least one element
                {
                    station.updateQuantity(); //updates the quantity
                    m_lstItem[i]->m_isFilled = true; //sets filled state
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber(); //sets serial number
                    os << "    Filled " << this->m_name << ", " << this->m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                else  //if station found but inventory is empty
                {
                    os << "    Unable to fill " << this->m_name << ", " << this->m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }

    }
    bool CustomerOrder::isItemFilled(std::string item) const
    {
        for (size_t i = 0u; i < m_cntItem; i++)
        {
            if (item == m_lstItem[i]->m_itemName) //checks if item exists
                return m_lstItem[i]->m_isFilled;
        }

        return true; //if item doesn't exist return true anyways
    }
    bool CustomerOrder::isFilled() const
    {
        bool check = true;

        for (size_t i = 0u; i < m_cntItem && check == true; i++)
        {
            if (m_lstItem[i]->m_isFilled)
            {
                //if it's true do nothing & simply continue looping
            }
            else   //if even ONE of the item's filledstate is false
            {
                check = false; //set check to false & terminates loop
            }
        }
        return check;
    }
    void CustomerOrder::display(std::ostream& os) const
    {
        os << std::left << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << setfill('0') << setw(6) << m_lstItem[i]->m_serialNumber << "]" << " " << setw(m_widthField) << setw(30) << setfill(' ') << std::left << m_lstItem[i]->m_itemName << std::right << (m_lstItem[i]->m_isFilled ? " - FILLED" : " - TO BE FILLED") << std::endl;
        }

    }

}
