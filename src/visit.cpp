#include "visit.h"
#include <unordered_map>

int val_stack_cnt = 0;
int val_stack_idx = 0;
bool has_call = false;
int func_arg_idx = 0;
std::unordered_map<koopa_raw_value_t, int> val_stack;

// 访问 raw program
void Visit(const koopa_raw_program_t &program) {
  // 执行一些其他的必要操作
  // ...
  // 访问所有全局变量
  Visit(program.values);
  // 访问所有函数
  Visit(program.funcs);
}

// 访问 raw slice
void Visit(const koopa_raw_slice_t &slice) {
  for (size_t i = 0; i < slice.len; ++i) {
    auto ptr = slice.buffer[i];
    // 根据 slice 的 kind 决定将 ptr 视作何种元素
    switch (slice.kind) {
      case KOOPA_RSIK_FUNCTION:
        // 访问函数
        Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
        break;
      case KOOPA_RSIK_BASIC_BLOCK:
        // 访问基本块
        Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
        break;
      case KOOPA_RSIK_VALUE:
        // 访问指令
        Visit(reinterpret_cast<koopa_raw_value_t>(ptr));
        break;
      default:
        // 我们暂时不会遇到其他内容, 于是不对其做任何处理
        assert(false);
    }
  }
}

// 访问函数
void Visit(const koopa_raw_function_t &func) {
  // 执行一些其他的必要操作
  // ...
  // 访问所有基本块
  val_stack_idx = 0;
  val_stack_cnt = 0;
  has_call = false;
  func_arg_idx = 0;
  int args_more_than_8 = 0;
  for(size_t i=0;i<func->bbs.len;i++){
    auto bb = reinterpret_cast<koopa_raw_basic_block_t>(func->bbs.buffer[i]);
    for(size_t j=0;j<bb->insts.len;j++){
      auto inst = reinterpret_cast<koopa_raw_value_t>(bb->insts.buffer[j]);
      if(inst->kind.tag == KOOPA_RVT_ALLOC||inst->kind.tag == KOOPA_RVT_BINARY||inst->kind.tag == KOOPA_RVT_LOAD||inst->kind.tag == KOOPA_RVT_BRANCH){
        val_stack_cnt += 4;
      }
      if(inst->kind.tag == KOOPA_RVT_CALL){
        has_call = true;
        if(inst->kind.data.call.callee->ty->data.function.ret->tag == KOOPA_RTT_INT32)
          val_stack_cnt += 4;
        if(int(inst->kind.data.call.args.len-8-args_more_than_8) > 0){
          args_more_than_8 = inst->kind.data.call.args.len-8-args_more_than_8;
        }
      }
    }
  }
  if(has_call){
    val_stack_cnt += 4;
  }
  val_stack_cnt += 4*args_more_than_8;
  val_stack_idx += 4*args_more_than_8;
  val_stack.clear();
  if(func->bbs.len > 0){
    std::cout << "\t.text\n";
    std::cout << "\t.globl " << func->name + 1 << "\n";
    std::cout << func->name + 1 << ":\n";
    std::cout << "\taddi sp, sp, -"<<val_stack_cnt<<"\n";
    std::cout << "\tsw ra, "<<val_stack_cnt-4<<"(sp)\n";
  }
  Visit(func->bbs);
}

// 访问基本块
void Visit(const koopa_raw_basic_block_t &bb) {
  // 执行一些其他的必要操作
  // ...
  // 访问所有指令
  if(std::string(bb->name+1) != "entry")
    std::cout<<bb->name+1<<":\n";
  Visit(bb->insts);
}

// 访问指令
void Visit(const koopa_raw_value_t &value) {
  // 根据指令类型判断后续需要如何访问
  const auto &kind = value->kind;
  switch (kind.tag) {
    case KOOPA_RVT_RETURN:
      // 访问 return 指令
      Visit(kind.data.ret);
      break;
    case KOOPA_RVT_INTEGER:
      // 访问 integer 指令
      Visit(kind.data.integer);
      break;
    case KOOPA_RVT_BINARY:
      // 访问 binary 指令
      Visit(kind.data.binary, value);
      break;
    case KOOPA_RVT_ALLOC:
      break;
    case KOOPA_RVT_STORE:
      Visit(kind.data.store, value);
      break;
    case KOOPA_RVT_LOAD:
      Visit(kind.data.load, value);
      break;
    case KOOPA_RVT_BRANCH:
      Visit(kind.data.branch);
      break;
    case KOOPA_RVT_JUMP:
      Visit(kind.data.jump);
      break;
    case KOOPA_RVT_CALL:
      // 访问 call 指令
      Visit(kind.data.call, value);
      break;
    case KOOPA_RVT_GLOBAL_ALLOC:
      Visit(kind.data.global_alloc, value);
      break;
    case KOOPA_RVT_GET_ELEM_PTR:
      Visit(kind.data.get_elem_ptr, value);
      break;
    case KOOPA_RVT_GET_PTR:
      break;
    default:
      std::cout<<kind.tag<<std::endl;
      // 其他类型暂时遇不到
      // assert(false);
  }
}

void Visit(const koopa_raw_return_t& ret) {
  if (ret.value != nullptr) {
    if (ret.value->kind.tag == KOOPA_RVT_INTEGER) {
      std::cout << "\tli a0, ";
      Visit(ret.value->kind.data.integer);
      std::cout << "\n";
    }
    else{
      std::cout << "\tlw a0, "<<val_stack[ret.value]<<"(sp)\n";
    }
  }
  if(has_call){
    std::cout<<"\tlw ra, "<<val_stack_cnt-4<<"(sp)\n";
  }
  std::cout<<"\taddi sp, sp, "<<val_stack_cnt<<"\n";
  std::cout << "\tret\n\n";
}

void Visit(const koopa_raw_integer_t& integer) {
  std::cout << integer.value;
}

void Visit(const koopa_raw_binary_t& binary, const koopa_raw_value_t& value){
  koopa_raw_value_t l = binary.lhs, r = binary.rhs;
  if(l->kind.tag == KOOPA_RVT_INTEGER){
    std::cout<<"\tli "<<"t0, "<<l->kind.data.integer.value<<"\n";
  }
  else{
    std::cout<<"\tlw t0, "<<val_stack[l]<<"(sp)\n";
  }
  if(r->kind.tag == KOOPA_RVT_INTEGER){
    std::cout<<"\tli "<<"t1, "<<r->kind.data.integer.value<<"\n";
  }
  else{
    std::cout<<"\tlw t1, "<<val_stack[r]<<"(sp)\n";
  }
  switch(binary.op){
    case KOOPA_RBO_ADD:
      std::cout<<"\tadd "<<"t0, "<<"t0, "<<"t1\n";
      break;
    case KOOPA_RBO_SUB:
      std::cout<<"\tsub "<<"t0, "<<"t0, "<<"t1\n";
      break;
    case KOOPA_RBO_EQ:
      std::cout<<"\txor "<<"t0, "<<"t0, "<<"t1\n";
      std::cout<<"\tseqz "<<"t0, "<<"t0\n";
      break;
    case KOOPA_RBO_NOT_EQ:
      std::cout<<"\txor "<<"t0, "<<"t0, "<<"t1\n";
      std::cout<<"\tsnez "<<"t0, "<<"t0\n";
      break;
    case KOOPA_RBO_MUL:
      std::cout<<"\tmul "<<"t0, "<<"t0, "<<"t1\n";
      break;
    case KOOPA_RBO_DIV:
      std::cout<<"\tdiv "<<"t0, "<<"t0, "<<"t1\n";
      break;
    case KOOPA_RBO_MOD:
      std::cout<<"\trem "<<"t0, "<<"t0, "<<"t1\n";
      break;
    case KOOPA_RBO_LT:
      std::cout<<"\tslt "<<"t0, "<<"t0, "<<"t1\n";
      break;
    case KOOPA_RBO_GT:
      std::cout<<"\tslt "<<"t0, "<<"t1, "<<"t0\n";
      break;
    case KOOPA_RBO_LE:
      std::cout<<"\tsgt "<<"t0, "<<"t0, "<<"t1\n";
      std::cout<<"\tseqz "<<"t0, "<<"t0\n";
      break;
    case KOOPA_RBO_GE:
      std::cout<<"\tslt "<<"t0, "<<"t0, "<<"t1\n";
      std::cout<<"\tseqz "<<"t0, "<<"t0\n";
      break;
    default:
      assert(false);
      break;
  }
  val_stack[value] = val_stack_idx;
  std::cout<<"\tsw "<<"t0, "<<val_stack_idx<<"(sp)\n";
  val_stack_idx += 4;
}

void Visit(const koopa_raw_load_t& load, const koopa_raw_value_t& value){
  if(load.src->kind.tag == KOOPA_RVT_ALLOC){
    std::cout<<"\tlw t0, "<<val_stack[load.src]<<"(sp)\n";
  }
  else if(load.src->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
    std::cout<<"\tla t0, "<<load.src->name+1<<"\n";
    std::cout<<"\tlw t0, 0(t0)\n";
  }
  if(val_stack.find(value)!=val_stack.end()){
    std::cout<<"\tsw "<<"t0, "<<val_stack[value]<<"(sp)\n";
  }
  else{
    val_stack[value] = val_stack_idx;
    std::cout<<"\tsw "<<"t0, "<<val_stack_idx<<"(sp)\n";
    val_stack_idx += 4;
  }
}

void Visit(const koopa_raw_store_t& store, const koopa_raw_value_t& value){
  if(val_stack.find(store.dest)==val_stack.end()&&store.dest->kind.tag != KOOPA_RVT_GLOBAL_ALLOC){
    val_stack[store.dest] = val_stack_idx;
    val_stack_idx += 4;
  }
  if(store.value->kind.tag == KOOPA_RVT_INTEGER){
    std::cout<<"\tli t0, "<<store.value->kind.data.integer.value<<"\n";
  }
  else if(store.value->kind.tag == KOOPA_RVT_FUNC_ARG_REF){

  }
  else{
    std::cout<<"\tlw t0, "<<val_stack[store.value]<<"(sp)\n";
  }

  if(store.value->kind.tag == KOOPA_RVT_FUNC_ARG_REF){
    if(func_arg_idx < 8){
      std::cout<<"\tsw a"<<func_arg_idx<<", "<<val_stack[store.dest]<<"(sp)\n";
    }
    else{
      std::cout<<"\tlw t0, "<<val_stack_cnt+(func_arg_idx-8)*4<<"(sp)\n";
      std::cout<<"\tsw t0, "<<val_stack[store.dest]<<"(sp)\n";
    }
    func_arg_idx++;
  }
  else if(store.dest->kind.tag == KOOPA_RVT_GLOBAL_ALLOC){
    std::cout<<"\tla t1, "<<store.dest->name+1<<"\n";
    std::cout<<"\tsw t0, 0(t1)\n";
  }
  else{
    std::cout<<"\tsw "<<"t0, "<<val_stack[store.dest]<<"(sp)\n";
  }
}

void Visit(const koopa_raw_jump_t& jump){
  std::cout<<"\tj "<<jump.target->name+1<<"\n";
}

void Visit(const koopa_raw_branch_t& branch){
  if(branch.cond->kind.tag == KOOPA_RVT_INTEGER){
    std::cout<<"\tli t0, "<<branch.cond->kind.data.integer.value<<"\n";
  }
  else{
    std::cout<<"\tlw t0, "<<val_stack[branch.cond]<<"(sp)\n";
  }
  std::cout<<"\tbnez "<<"t0, "<<branch.true_bb->name+1<<"\n";
  std::cout<<"\tj "<<branch.false_bb->name+1<<"\n";
}

void Visit(const koopa_raw_call_t& call, const koopa_raw_value_t& value){
  int a_reg_cnt = 0;
  int args_stack_idx = 0;
  for(size_t i=0;i<call.args.len;i++){
    auto arg = reinterpret_cast<koopa_raw_value_t>(call.args.buffer[i]);
    if(i<8){
      if(arg->kind.tag == KOOPA_RVT_INTEGER){
        std::cout<<"\tli a"<<a_reg_cnt<<", "<<arg->kind.data.integer.value<<"\n";
      }
      else{
        std::cout<<"\tlw a"<<a_reg_cnt<<", "<<val_stack[arg]<<"(sp)\n";
      }
      a_reg_cnt++;
    }
    else{
      if(arg->kind.tag == KOOPA_RVT_INTEGER){
        std::cout<<"\tli t0, "<<arg->kind.data.integer.value<<"\n";
        std::cout<<"\tsw t0, "<<args_stack_idx<<"(sp)\n";
      }
      else{
        std::cout<<"\tlw t0, "<<val_stack[arg]<<"(sp)\n";
        std::cout<<"\tsw t0, "<<args_stack_idx<<"(sp)\n";
      }
      args_stack_idx += 4;
    }
  }
  std::cout<<"\tcall "<<call.callee->name+1<<"\n";
  //store return 
  if(call.callee->ty->data.function.ret->tag == KOOPA_RTT_INT32){
    val_stack[value] = val_stack_idx;
    std::cout<<"\tsw a0, "<<val_stack_idx<<"(sp)\n";
    val_stack_idx += 4;
  }
}

void Visit(const koopa_raw_global_alloc_t& global_alloc, const koopa_raw_value_t& value){
  std::cout<<"\t.data\n";
  std::cout<<"\t.global "<<value->name+1<<"\n";
  std::cout<<value->name+1<<":\n";
  std::cout<<"\t.word "<<global_alloc.init->kind.data.integer.value<<"\n\n";
}