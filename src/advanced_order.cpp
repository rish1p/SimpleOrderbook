/*
Copyright (C) 2017 Jonathon Ogden < jeog.dev@gmail.com >

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses.
*/

#include "../include/advanced_order.hpp"

namespace sob{

bool
OrderParamaters::operator==(const OrderParamaters& op) const
{
    return _is_buy == op._is_buy
            && _size == op._size
            && _limit == op._limit
            && _stop == op._stop;
}

order_type
OrderParamaters::get_order_type() const
{
    if( !(*this) ){
        return order_type::null;
    }
    if( _stop ){
        return _limit ? order_type::stop_limit : order_type::stop;
    }
    return _limit ? order_type::limit : order_type::market;
}

AdvancedOrderTicket::AdvancedOrderTicket( order_condition condition,
                                          condition_trigger trigger,
                                          OrderParamaters order1,
                                          OrderParamaters order2 )
    :
        _condition(condition),
        _trigger(trigger),
        _order1(order1),
        _order2(order2)
    {
    }

bool
AdvancedOrderTicket::operator==(const AdvancedOrderTicket& aot) const
{
    return _condition == aot._condition
            && _trigger == aot._trigger
            && _order1 == aot._order1
            && _order2 == aot._order2;
}

AdvancedOrderTicketOCO::AdvancedOrderTicketOCO( condition_trigger trigger,
                                                bool is_buy,
                                                size_t size,
                                                double limit,
                                                double stop )
    :
        AdvancedOrderTicket( condition, trigger,
                OrderParamaters(is_buy, size, limit, stop), OrderParamaters() )
    {
        if( size == 0 ){
            throw advanced_order_error("invalid order size");
        }
    }

AdvancedOrderTicketOTO::AdvancedOrderTicketOTO( condition_trigger trigger,
                                                bool is_buy,
                                                size_t size,
                                                double limit,
                                                double stop )
    :
        AdvancedOrderTicket( condition, trigger,
                OrderParamaters(is_buy, size, limit, stop), OrderParamaters() )
    {
        if( size == 0 ){
            throw advanced_order_error("invalid order size");
        }
    }

const AdvancedOrderTicket AdvancedOrderTicket::null(
    order_condition::none,
    condition_trigger::none
);

const condition_trigger AdvancedOrderTicket::default_trigger =
        condition_trigger::fill_partial;

const order_condition AdvancedOrderTicketOCO::condition =
        order_condition::one_cancels_other;

const order_condition AdvancedOrderTicketOTO::condition =
        order_condition::one_triggers_other;


}; /* sob */



