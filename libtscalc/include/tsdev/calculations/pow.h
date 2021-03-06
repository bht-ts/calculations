#ifndef tsdev_calculations_pow_h
#define tsdev_calculations_pow_h

#include "binaryoperator.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TLhs, typename TRhs>
        struct _Pow : public BinaryOperator<T, TLhs, TRhs> {
            _Pow(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs)
                : BinaryOperator<T, TLhs, TRhs>(lhs, rhs)
            {}

            virtual void execute() {
                BinaryOperator<T, TLhs, TRhs>::execute();

                this->value.value = std::pow(this->lhs->value.value,this->rhs->value.value);
                this->value.unit = this->lhs->value.unit;

                for(int i = 0; i < this->rhs->value.value-1; ++i) {
                    this->value.unit.add(this->lhs->value.unit);
                }

                this->optimizeUnit();
            }

            virtual std::string symbol() const {
                return "^";
            }

            virtual bool bracketLHS() const {
                return !this->value.unit.isEmpty();
            }
        };

        template <typename TLhs, typename TRhs>
        ElementPtr<double> Pow(const ElementPtr<TLhs>& lhs, const ElementPtr<TRhs>& rhs) {
            return ElementPtr<double>(new _Pow<TLhs, TLhs, TRhs>(lhs, rhs));
        }

        template <typename TLhs>
        ElementPtr<double> Pow(ElementPtr<TLhs> lhs, double rhs) {
            ElementPtr<double> erhs = Stack<double>::instance().createElement(new Element<double>(rhs));
            return ElementPtr<double>(new _Pow<double, TLhs, double>(lhs, erhs));
        }

        template <typename TRhs>
        ElementPtr<double> Pow(double lhs, ElementPtr<TRhs> rhs) {
            ElementPtr<double> elhs = Stack<double>::instance().createElement(new Element<double>(lhs));
            return ElementPtr<double>(new _Pow<double, double, TRhs>(elhs, rhs));
        }
    }
}

#endif

