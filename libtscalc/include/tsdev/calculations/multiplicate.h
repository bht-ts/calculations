#ifndef tsdev_calculations_multiplicate_h
#define tsdev_calculations_multiplicate_h

#include "binaryoperator.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TLhs, typename TRhs>
        struct _Multiplicate : public BinaryOperator<T, TLhs, TRhs> {
            _Multiplicate(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs)
                : BinaryOperator<T, TLhs, TRhs>(lhs, rhs)
            {}

            virtual void execute() {
                BinaryOperator<T, TLhs, TRhs>::execute();

                this->setValue(this->lhs->value.value * this->rhs->value.value);
                this->setUnit(this->lhs->value.unit.copy().add(this->rhs->value.unit));
            }

            virtual std::string symbol() const {
                return "*";
            }
        };

        template <typename TLhs, typename TRhs>
        ElementPtr<double> operator*(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs) {
            return ElementPtr<double>(new _Multiplicate<double, TLhs, TRhs>(lhs, rhs));
        }

        template <typename TLhs>
        ElementPtr<double> operator*(ElementPtr<TLhs> lhs, double rhs) {
            ElementPtr<double> erhs = Stack<double>::instance().createElement(new Element<double>(rhs));
            return ElementPtr<double>(new _Multiplicate<double, TLhs, double>(lhs, erhs));
        }

        template <typename TRhs>
        ElementPtr<double> operator*(double lhs, ElementPtr<TRhs> rhs) {
            ElementPtr<double> elhs = Stack<double>::instance().createElement(new Element<double>(lhs));
            return ElementPtr<double>(new _Multiplicate<double, double, TRhs>(elhs, rhs));
        }
    }
}

#endif
