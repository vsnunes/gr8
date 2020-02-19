#ifndef __GR8_SEMANTICS_SYMBOL_H__
#define __GR8_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace gr8 {

  class symbol {
    basic_type *_type;
    std::string _name;
    int _offset; // hack!
    int _enter_val = 0;
    int _functionType = 0;
    /** Need for postfix to choose LOCAL or ADDR **/
    bool _isGlobal = true;
    /** To store function arguments id **/
    std::vector<int> _functionArgs;

  public:
    symbol(basic_type *type, const std::string &name, int offset) :
        _type(type), _name(name), _offset(offset) {
    }

    virtual ~symbol() {
      delete _type;
    }

    basic_type *type() const {
      return _type;
    }
    const std::string &name() const {
      return _name;
    }
    int offset() const {
      return _offset;
    }
    int offset(int v) {
      return _offset = v;
    }
    int enter_val() const{
        return _enter_val;
    }
    int enter_val(int val){
        return _enter_val = val;
    }
    int functionType() const{
        return _functionType;
    }
    int functionType(int val){
        return _functionType = val;
    }

    int isGlobal() const{
        return _isGlobal;
    }
    int isGlobal(bool val){
        return _isGlobal = val;
    }

    std::vector<int> functionArgs() const{
        return _functionArgs;
    }

    void addfunctionArgsId(int sizeBytes) {
        _functionArgs.push_back(sizeBytes);
    }
    
  };

} // gr8

#endif
