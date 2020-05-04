#pragma once

#include <stdafx.h>
#include <boost/uuid/uuid.hpp>

class BaseModel
{
protected:
    boost::uuids::uuid _id;

public:
    BaseModel();
    virtual ~BaseModel();

	boost::uuids::uuid id() const { return _id; }

    virtual const char* table_name() const = 0;
};