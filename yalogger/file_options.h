//
//  file_options.h
//  logger
//
//  Created by Dmitry Danilov on 31.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef __logger__file_options__
#define __logger__file_options__

#include "defs.h"
#include <ios>

namespace ya {
class file_options {
public:
    file_options() : m_filename(TEXT("")), m_open_mode(std::ios_base::ate | std::ios_base::app), stop_immediately(false) {}
    file_options(const string_t& filename, std::ios_base::openmode mode, bool is_stop_immediately) :
        m_filename(filename), m_open_mode(mode), stop_immediately(is_stop_immediately) {}
    
    void set_filename(const string_t& filename) { m_filename = filename; }
    const string_t& filename() const { return m_filename; }
    
    void set_mode(std::ios_base::openmode mode) { m_open_mode = mode; }
    std::ios_base::openmode mode() const { return m_open_mode; }

    void set_stop_immediately(bool is_stop_immediately) { stop_immediately = is_stop_immediately; }
    bool is_stop_immediately() const { return stop_immediately; }
private:
    string_t m_filename;
    std::ios_base::openmode m_open_mode;
    bool stop_immediately;
};
    
}
#endif /* defined(__logger__file_options__) */
