#pragma once
#include <map>
#include <string>
#include <vector>

class text_filter {
public:
    text_filter(std::string const& text, std::string const& filter);
    ~text_filter();

private:
    using char_map = std::map<char, std::vector<size_t>>;
    using strings = std::vector<std::string>;
    using string_size_t_map = std::map<std::string, std::vector<size_t>>;

    void create_text_map(std::string const& text);
    void create_filters(std::string const& filters);
    void do_text_filters();
    void do_single_text_filter(std::string const& filter);
    void find_matched_string(std::string const& filter, std::vector<size_t> const& poses);

    std::string full_text;
    char_map text_chars;
    strings text_filters;
    string_size_t_map match_poses;
};