// Name: Ahmad Jafari
// Seneca Student ID:143469195
// Seneca email: mjafari22@myseneca.ca
// Date of completion:26/07/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignment.

#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H
#include "Station.h"
#include <string>

namespace sdds {
    class CustomerOrder {
        struct Item
        {
            std::string m_itemName;
            size_t m_serialNumber{ 0 };
            bool m_isFilled{ false };

            Item(const std::string& src) : m_itemName(src) {};
        };

        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;

    public:
        static size_t m_widthField;
        CustomerOrder();
        CustomerOrder(std::string& record);
        CustomerOrder(const CustomerOrder& src);
        CustomerOrder(CustomerOrder&& src) noexcept;
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;
        ~CustomerOrder();
        void fillItem(Station& station, std::ostream& os);
        bool isItemFilled(std::string item) const;
        bool isFilled() const;
        void display(std::ostream& os) const;
    };
}

#endif // SDDS_CUSTOMER_ORDER_H

