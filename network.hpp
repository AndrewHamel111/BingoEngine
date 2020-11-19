// FROM NICK GAME AKA MANY FACES OF NICKTOBER
// https://github.com/AndrewHamel111/sm64ds_wanted

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>

std::string getBodyFromURL(std::string url);
bool sendPostRequest(std::string url, std::string post);

#endif