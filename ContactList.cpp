#include "ContactList.h"
#include <iostream>

ContactList::ContactList() {}

ContactList::~ContactList() {}

void ContactList::addContact(const std::string &name, const ContactInfo &info) {
    //TODO
    
    contacts.put(name, info);
    
}

bool ContactList::deleteContact(const std::string &name) {
    //TODO
    
    return contacts.deletekey(name);
    
}

void ContactList::updateContact(const std::string &name, const ContactInfo &newInfo) {
    //TODO
    
    if (contacts.containsKey(name)) {
        contacts.put(name, newInfo);
    }
    
}



const ContactInfo &ContactList::getContact(const std::string &name) const {
    //TODO
    
    return contacts.get(name);
    
}



void ContactList::iterateAlphabetically()  {            //ÇALIŞMIYOR
// TODO
/*
    if (contacts.size() == 0) {
        std::cout << "Contact list is empty." << std::endl;
        return;
    }
    
    // Collect all entries using inorder traversal
    std::vector<KeyValuePair<std::string, ContactInfo> > allEntries;
    
    try {
        KeyValuePair<std::string, ContactInfo> current = contacts.firstEntry();
        allEntries.push_back(current);
        
        // Keep getting next entries until we've visited all
        while (true) {
            try {
                current = contacts.getNext(current.getKey());
                allEntries.push_back(current);
            } catch (const NoSuchItemException&) {
                break;
            }
        }
    } catch (const NoSuchItemException&) {
        return;
    }
    
    // Print all contacts
    for (const auto& entry : allEntries) {
        std::cout << "Name: " << entry.getKey() << std::endl;
        const ContactInfo& info = entry.getValue();
        
        // Print phone numbers
        std::cout << "  Phone Numbers: ";
        if (info.phoneNumbers.empty()) {
            std::cout << "None";
        } else {
            for (size_t i = 0; i < info.phoneNumbers.size(); ++i) {
                std::cout << info.phoneNumbers[i];
                if (i + 1 < info.phoneNumbers.size()) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
        
        // Print email
        std::cout << "  Email: " << (info.email.empty() ? "None" : info.email) << std::endl;
        
        // Print company
        std::cout << "  Company: " << (info.company.empty() ? "None" : info.company) << std::endl;
        
        // Print notes
        std::cout << "  Notes: " << (info.notes.empty() ? "None" : info.notes) << std::endl;
        std::cout << std::endl;
    }
*/
}

