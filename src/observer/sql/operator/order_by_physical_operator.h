#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator();
  explicit OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>> &condition)
      : expressions(std::move(condition))
  {}

  virtual ~OrderByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  void set_calc(const Value &v, DistanceType type)
  {
    Value real;
    Value::cast_to(v, AttrType::VECTORS, real);
    calc_ = std::make_unique<calc>(v, type);
  }

  RC     open(Trx *trx) override;
  RC     next() override;
  RC     close() override;
  Tuple *current_tuple() override;

private:
  struct calc
  {
    calc(const Value &f, DistanceType type) : distance_type_(type), v(f) {}
    RC operator()(const Value &a, Value &value) const
    {
      switch (distance_type_) {
        case L2: return Value::l2_distance(a, v, value);
        case IP: return Value::inner_product(a, v, value);
        case COSINE: return Value::cosine_distance(a, v, value);
        default: return RC::INVALID_ARGUMENT;
      }
    }
    DistanceType distance_type_;

    Value v;
  };

  Trx                                     *trx_   = nullptr;
  int                                      index_ = -2;
  ValueListTuple                           tuple_;
  std::unique_ptr<calc>                    calc_;
  std::vector<std::vector<Value>>          tuple_in_value;
  std::vector<std::unique_ptr<Expression>> expressions;
};
