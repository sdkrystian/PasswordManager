// Copyright 2018 Krystian Stasiowski

#include "UserInfo.h"

std::vector<Category> UserInfo::categories_;
std::string UserInfo::Configuration;

void UserInfo::MoveConfig(const std::string& path)
{
  remove((Configuration + "\\information.xml").c_str());
  Configuration = path;
  Save();
}

std::vector<Category>& UserInfo::Categories()
{
  return categories_;
}

void UserInfo::Save()
{
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
  decl->append_attribute(doc.allocate_attribute("version", "1.0"));
  decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
  doc.append_node(decl);

  rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "Information");
  doc.append_node(root);

  for (Category& c : categories_)
  {
    rapidxml::xml_node<>* category = doc.allocate_node(rapidxml::node_element, "Category");
    rapidxml::xml_attribute<>* name = doc.allocate_attribute("name", c.name.c_str());
    category->append_attribute(name);
    root->append_node(category);
    for (Entry& e : c.entries)
    {
      rapidxml::xml_node<>* entry = doc.allocate_node(rapidxml::node_element, "Entry");
      rapidxml::xml_attribute<>* name = doc.allocate_attribute("name", e.name.c_str());
      entry->append_attribute(name);
      rapidxml::xml_attribute<>* username = doc.allocate_attribute("username", e.username.c_str());
      entry->append_attribute(username);
      rapidxml::xml_attribute<>* email = doc.allocate_attribute("email", e.email.c_str());
      entry->append_attribute(email);
      rapidxml::xml_attribute<>* password = doc.allocate_attribute("password", e.password.c_str());
      entry->append_attribute(password);
      rapidxml::xml_attribute<>* url = doc.allocate_attribute("url", e.url.c_str());
      entry->append_attribute(url);
      rapidxml::xml_attribute<>* note = doc.allocate_attribute("note", e.note.c_str());
      entry->append_attribute(note);
      category->append_node(entry);
    }
  }
  std::ofstream file(Configuration + "\\information.xml");
  file << doc;
  file.close();
  doc.clear();
}

void UserInfo::ReadFromFile()
{
  categories_.clear();
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<> * rootnode;
  std::ifstream file(Configuration + "\\information.xml");
  std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  buffer.push_back('\0');
  doc.parse<0>(&buffer[0]);
  rootnode = doc.first_node("Information");
  for (rapidxml::xml_node<>* categorynode = rootnode->first_node("Category"); categorynode; categorynode = categorynode->next_sibling())
  {
    Category category;
    category.name = categorynode->first_attribute("name")->value();
    for (rapidxml::xml_node<>* entrynode = categorynode->first_node("Entry"); entrynode; entrynode = entrynode->next_sibling())
    {
      Entry entry;
      entry.name = entrynode->first_attribute("name")->value();
      entry.username = entrynode->first_attribute("username")->value();
      entry.email = entrynode->first_attribute("email")->value();
      entry.password = entrynode->first_attribute("password")->value();
      entry.url = entrynode->first_attribute("url")->value();
      entry.note = entrynode->first_attribute("note")->value();
      category.entries.push_back(entry);
    }
    categories_.push_back(category);
  }
}