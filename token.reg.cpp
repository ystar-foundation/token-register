#include <token.reg.hpp>

void tokenreg::addaccmng( const name& acc ) {
   require_auth( get_self() );
   check( is_account( acc ), "account doesn't exist when addaccmng");
   accmngs _accmng( get_self(), get_self().value );
   auto am = _accmng.find( acc.value );
   check( am == _accmng.end(), "account has already registered as accmng" );

   _accmng.emplace(get_self(), [&](auto &row) {
      row.manager = acc;
   });
}

void tokenreg::rmvaccmng( const name& acc ) {
   require_auth( get_self() );
   check( is_account( acc ), "account doesn't exist when rmvaccmng");
   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( acc.value,  "is not a manager account");
   _accmng.erase(am);
}

void tokenreg::keyreg( const name&   manager, const asset&  max_supply, const name&   issuer, uint32_t      tokenno ) {
   require_auth( manager );
   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( manager.value,  "operator is not a manager account" );
}

void tokenreg::regtoken(const name& manager, const string& tknsymstr, uint8_t digit, const string& tokenname, const string& issuechain,
                        const name& contractacc, const string& contractname, uint32_t contractno, const name& adminacc,
                        const name& issuer, const string& issuerurl, const string& issuerid, const string& issueradd, const string& issuertel,
                        const name regacc, const string& memo ) {
   require_auth( manager );
   check( tknsymstr.size() < 8, "token symbol code has more than 7 bytes" );
   check( tokenname.size() <= 128, "tokenname has more than 128 bytes" );
   check( issuechain.size() <= 128, "issuechain has more than 128 bytes" );
   check( contractname.size() <= 128, "contractname has more than 128 bytes" );
   check( issuerurl.size() <= 128, "issuerurl has more than 128 bytes" );
   check( issuerid.size() <= 128, "issuerid has more than 128 bytes" );
   check( issueradd.size() <= 128, "issueradd has more than 128 bytes" );
   check( issuertel.size() <= 16, "issuertel has more than 16 bytes" );
   check( memo.size() <= 256, "memo has more than 256 bytes" );

   /*
   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( manager.value,  "operator is not a manager account" );
   symbol sym = symbol(symbol_code(tknsymstr), digit);
   check( sym.is_valid(), "invalid symbol" );
   auto tokenno = sym.code().raw();
   asset supply( 0, sym );
   tokeninfos _tokeninfo( get_self(), get_self().value );
   const auto& ti = _tokeninfo.find( tokenno );
   check( ti == _tokeninfo.end(), "this token has already been registered" );
   uint64_t current_time = current_time_point().sec_since_epoch(); //seconds

   _tokeninfo.emplace(manager, [&](auto &row) {
      row.tokenno = tokenno;
      row.tokenname = tokenname;
      row.issuechain = issuechain;
      row.contractacc = contractacc;
      row.contractname = contractname;
      row.adminacc = adminacc;
      row.issuer = issuer;
      row.issuerurl = issuerurl;
      row.issuerid = issuerid;
      row.issueradd = issueradd;
      row.issuertel = issuertel;
      row.supply = supply;
      row.max_supply = supply;
      row.regacc = regacc;
      row.regtime = current_time;
      row.updatetime = current_time;
      row.memo = memo;
   });

   regcount_singleton _regcount( get_self(), get_self().value );
   regcount regtkncount;
   regtkncount = _regcount.exists() ? _regcount.get() : regcount{};
   regtkncount.total_regtokens += 1;
   _regcount.set( regtkncount, get_self() );*/

   reginfo_singleton _reginfo( get_self(), get_self().value );
   reginfo regtkninfo;
   if ( _reginfo.exists() ) {
      regtkninfo = _reginfo.get();
   } else {
      regtkninfo = reginfo{};
      regtkninfo.next_tokenno = 100000;
      regtkninfo.tokens_count = 0;
   }
   regtkninfo.next_tokenno += 1;
   auto tokenno = regtkninfo.next_tokenno;
   _reginfo.set( regtkninfo, manager );
}

void tokenreg::modtoken(const name& modifier, const string& tknsymstr, uint8_t digit, const string& tokenname, const string& issuechain,
                        const name& contractacc, const string& contractname, uint32_t contractno, const name& adminacc,
                        const name& issuer, const string& issuerurl, const string& issuerid, const string& issueradd, const string& issuertel,
                        const name regacc, const string& memo ) {
   require_auth( modifier );
   check( tknsymstr.size() < 8, "token symbol code has more than 7 bytes" );
   check( tokenname.size() <= 128, "tokenname has more than 128 bytes" );
   check( issuechain.size() <= 128, "issuechain has more than 128 bytes" );
   check( contractname.size() <= 128, "contractname has more than 128 bytes" );
   check( issuerurl.size() <= 128, "issuerurl has more than 128 bytes" );
   check( issuerid.size() <= 128, "issuerid has more than 128 bytes" );
   check( issueradd.size() <= 128, "issueradd has more than 128 bytes" );
   check( issuertel.size() <= 16, "issuertel has more than 16 bytes" );
   check( memo.size() <= 256, "memo has more than 256 bytes" );
   symbol sym = symbol(symbol_code(tknsymstr), digit);
   check( sym.is_valid(), "invalid symbol" );
   tokeninfos _tokeninfo( get_self(), get_self().value );
   const auto& ti = _tokeninfo.get( sym.code().raw(), "this token has not been registered" );
   check( sym == ti.max_supply.symbol, "symbol mismatch" );
   check( modifier == ti.regacc, "modifier is not the regist account" );
   uint64_t current_time = current_time_point().sec_since_epoch();

   _tokeninfo.modify(ti, modifier, [&](auto &row) {
      row.tokenname = tokenname;
      row.issuechain = issuechain;
      row.contractacc = contractacc;
      row.contractname = contractname;
      row.contractno = contractno;
      row.adminacc = adminacc;
      row.issuer = issuer;
      row.issuerurl = issuerurl;
      row.issuerid = issuerid;
      row.issueradd = issueradd;
      row.issuertel = issuertel;
      row.regacc = regacc;
      row.updatetime = current_time;
      row.memo = memo;
   });
}

void tokenreg::rmvtoken(const name& manager, const string& tknsymstr, uint8_t digit, const string& memo) {
   require_auth( manager );
   check( tknsymstr.size() < 8, "token symbol code has more than 7 bytes" );
   check( memo.size() <= 256, "memo has more than 256 bytes" );
   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( manager.value,  "operator is not a manager account" );
   symbol sym = symbol(symbol_code(tknsymstr), digit);
   check( sym.is_valid(), "invalid symbol" );

   tokeninfos _tokeninfo( get_self(), get_self().value );
   const auto& ti = _tokeninfo.get( sym.code().raw(), "this token has not been registered" );
   check( sym == ti.max_supply.symbol, "symbol precision mismatch" );
   _tokeninfo.erase(ti);

   /*
   regcount_singleton _regcount( get_self(), get_self().value );
   regcount regtkncount;
   check( _regcount.exists(), "token regcount is null" );
   regtkncount = _regcount.get();
   if (regtkncount.total_regtokens > 0) {
      regtkncount.total_regtokens -= 1;
   }
   _regcount.set( regtkncount, get_self() );
   */
}

void tokenreg::setsupply(const name& manager, const string& tknsymstr, uint8_t digit, const asset& supply, const asset& max_supply, const string& memo) {
   require_auth( manager );
   check( tknsymstr.size() < 8, "token symbol code has more than 7 bytes" );
   check( memo.size() <= 256, "memo has more than 256 bytes" );
   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( manager.value,  "operator is not a manager account" );
   symbol sym = symbol(symbol_code(tknsymstr), digit);
   check( sym.is_valid(), "invalid symbol" );

   tokeninfos _tokeninfo( get_self(), get_self().value );
   const auto& ti = _tokeninfo.get( sym.code().raw(), "this token has not been registered" );
   check( sym == ti.max_supply.symbol, "symbol precision mismatch" );
   _tokeninfo.modify(ti, manager, [&](auto &row) {
      row.supply = supply;
      row.max_supply = max_supply;
   });
}

void tokenreg::setregfee( const asset& reg_fee ) {
   require_auth( get_self() );
   symbol sym = reg_fee.symbol;
   check( sym.is_valid(), "invalid symbol" );
   regfee_singleton _regfee( get_self(), get_self().value );
   regfee regtknfee = regfee{};
   regtknfee.reg_fee = reg_fee;
   _regfee.set( regtknfee, get_self() );
}

void tokenreg::transfer( const name& from, const name& to, const asset& quantity, const string& memo ) {
   check( memo == std::string("register token"), "register token memo error" );

   regfee_singleton _regfee( get_self(), get_self().value );
   regfee regtknfee;
   if ( _regfee.exists() ) {
      regtknfee = _regfee.get();
      check( quantity == regtknfee.reg_fee, "register fee's error" );
   } else {
      check( quantity.amount == 100000000000, "register token just need 100.0000 YTA" );
   }

   reginfo_singleton _reginfo( get_self(), get_self().value );
   reginfo regtkninfo;
   if ( _reginfo.exists() ) {
      regtkninfo = _reginfo.get();
   } else {
      regtkninfo = reginfo{};
      regtkninfo.next_tokenno = 100000;
      regtkninfo.tokens_count = 0;
   }
   regtkninfo.next_tokenno += 1;
   auto tokenno = regtkninfo.next_tokenno;
   _reginfo.set( regtkninfo, get_self() );

   userregs _userreg( get_self(), get_self().value );
   auto ur = _userreg.find( from.value );
   if ( ur == _userreg.end() ) {
      _userreg.emplace(get_self(), [&](auto &row) {
         row.user = from;
         row.reg_count = 0;
         row.total_count = 1;
         row.next_tokenno = tokenno;
      });
   } else {
      check( ur->reg_count == ur->total_count, "you already have an unregistered token" );
      _userreg.modify(ur, get_self(), [&](auto &row) {
         row.total_count += 1;
         row.next_tokenno = tokenno;
      });
   }
}

void tokenreg::addcount( const name& creater, const string& memo ) {
   check( memo == std::string("register token"), "register token memo error" );
   require_auth( get_self() );

   reginfo_singleton _reginfo( get_self(), get_self().value );
   reginfo regtkninfo;
   if ( _reginfo.exists() ) {
      regtkninfo = _reginfo.get();
   } else {
      regtkninfo = reginfo{};
      regtkninfo.next_tokenno = 100000;
      regtkninfo.tokens_count = 0;
   }
   regtkninfo.next_tokenno += 1;
   auto tokenno = regtkninfo.next_tokenno;
   _reginfo.set( regtkninfo, get_self() );

   userregs _userreg( get_self(), get_self().value );
   auto ur = _userreg.find( creater.value );
   if ( ur == _userreg.end() ) {
      _userreg.emplace(get_self(), [&](auto &row) {
         row.user = creater;
         row.reg_count = 0;
         row.total_count = 1;
         row.next_tokenno = tokenno;
      });
   } else {
      check( ur->reg_count == ur->total_count, "you already have an unregistered token" );
      _userreg.modify(ur, get_self(), [&](auto &row) {
         row.total_count += 1;
         row.next_tokenno = tokenno;
      });
   }
}

void tokenreg::simreg( const name& manager, const name& issuer, const asset& maximum_supply, const string& tokenname, const string& memo ) {
   require_auth( manager );
   check( memo.size() <= 256, "memo has more than 256 bytes" );

   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( manager.value,  "operator is not a manager account" );

   symbol sym = maximum_supply.symbol;
   check( sym.is_valid(), "invalid symbol" );
   asset supply( 0, sym );

   uint64_t current_time = current_time_point().sec_since_epoch(); //seconds

   userregs _userreg( get_self(), get_self().value );
   const auto& ur = _userreg.get( issuer.value, "You need to buy a token permission." );
   check( ur.total_count == ur.reg_count + 1, "You need to buy a new token permission again." );
   auto tokenno = ur.next_tokenno;

   tokeninfos _tokeninfo( get_self(), get_self().value );
   auto ti = _tokeninfo.find( sym.code().raw() );
   check( ti == _tokeninfo.end(), "this token has already been registered" );

   _tokeninfo.emplace(manager, [&](auto &row) {
      row.tokenno = tokenno;
      row.tokenname = tokenname;
      //row.issuechain = issuechain;
      row.contractacc = get_self();
      //row.contractname = contractname;
      row.adminacc = issuer;
      row.issuer = issuer;
      row.supply = supply;
      row.max_supply = maximum_supply;
      row.regacc = issuer;
      row.regtime = current_time;
      row.updatetime = current_time;
      row.memo = memo;
   });

   _userreg.modify(ur, same_payer, [&](auto &row) {
      row.reg_count += 1;
   });

   reginfo_singleton _reginfo( get_self(), get_self().value );
   reginfo regtkninfo;
   check( _reginfo.exists(), "reginfo error" );
   regtkninfo = _reginfo.get();
   regtkninfo.tokens_count += 1;
   _reginfo.set( regtkninfo, get_self() );
}

void tokenreg::updatesupply( uint8_t mngtype, const name& manager, const name& contractacc, const asset& supply ) {
   auto sym = supply.symbol;
   check( sym.is_valid(), "invalid symbol" );
   tokeninfos _tokeninfo( get_self(), get_self().value );
   const auto& ti = _tokeninfo.get( sym.code().raw(), "this token has not been registered" );

   require_auth( manager );
   accmngs _accmng( get_self(), get_self().value );
   const auto& am = _accmng.get( manager.value,  "operator is not a manager account" );

   if (mngtype == 1) {
      check( supply.is_valid(), "invalid supply" );
      check( supply.amount > 0, "must issue positive supply" );
      check( supply.symbol == ti.max_supply.symbol, "symbol or precision mismatch" );
      _tokeninfo.modify(ti, same_payer, [&](auto &row) {
         row.supply = supply;
      });
      return;
   }

   stats statstable( contractacc, sym.code().raw() );
   const auto& st = statstable.get( sym.code().raw(), "token does not exist" );
   
   check( st.supply.is_valid(), "invalid supply" );
   check( st.supply.amount > 0, "must issue positive supply" );
   check( st.supply.symbol == ti.max_supply.symbol, "symbol or precision mismatch" );
   check( st.supply.amount != ti.supply.amount, "needn't update" );
   _tokeninfo.modify(ti, same_payer, [&](auto &row) {
      row.supply = st.supply;
   });

}
