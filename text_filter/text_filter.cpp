#include "text_filter.h"
#include <Windows.h>
#include <iostream>
#include <sstream>

text_filter::text_filter(std::string const& text, std::string const& filter)
    : full_text(text)
{
    create_filters(filter);
    auto start = GetTickCount();
    create_text_map(text);
    auto end = GetTickCount();
    std::cout << "Time to crate text map: " << end - start << std::endl;
    start = end;
    do_text_filters();
    end = GetTickCount();
    std::cout << "Time to filter text: " << end - start << std::endl;
}

void text_filter::create_filters(std::string const& filters) {
    std::istringstream sin(filters);
    for (std::string str; sin >> str; ) {
        text_filters.push_back(str);
    }
}

void text_filter::create_text_map(std::string const& text) {
    for (size_t i = 0; i < text.length(); ++i) {
        text_chars[text[i]].push_back(i);
    }
}

void text_filter::do_text_filters() {
    for (auto const& filter : text_filters) {
        match_poses[filter] = {};
        do_single_text_filter(filter);
    }
}

void text_filter::do_single_text_filter(std::string const& filter) {
    if (!filter.empty()) {
        auto it = text_chars.find(filter[0]);
        if (it != text_chars.end()) {
            find_matched_string(filter, it->second);
        }
    }
}

void text_filter::find_matched_string(std::string const& filter, std::vector<size_t> const& poses) {
    for (auto pos : poses) {
        if (!full_text.compare(pos, filter.length(), filter)) {
            match_poses[filter].push_back(pos);
        }
    }
}

text_filter::~text_filter() {
}