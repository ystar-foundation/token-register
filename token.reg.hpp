#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <eosio/singleton.hpp>

#include <string>
using namespace eosio;

using std::string;

/**
 * token.reg contract.
 */
class [[eosio::contract("token.reg")]] tokenreg : public contract {
   public:
      using contract::contract;

      /**
       * This action will add acc to accmng.
       *
       * @param acc - which account.
       */
      [[eosio::action]]
      void addaccmng( const name& acc );

      /**
       * This action will remove acc from accmng.
       *
       * @param acc - which account.
       */
      [[eosio::action]]
      void rmvaccmng( const name&  acc );

      /**
       * Regist one YottaChain's token by key.
       *
       * @param manager - which account performs this action,
       * @param max_supply - the max_supply,
       * @param issuer - the issuer,
       * @param tokenno - token number.
       */
      [[eosio::action]]
      void keyreg( const name&   manager,
                   const asset&  max_supply,
                   const name&   issuer,
                   uint32_t      tokenno );

      /**
       * Regist one YottaChain's token.
       *
       * @param manager - which account performs this action,
       * @param tknsymstr - token symbol string,
       * @param digit - decimal digit
       * @param tokenname - token name,
       * @param issuechain - issue in which chain,
       * @param contractacc - account for the deployment contract,
       * @param contractname - the contract's name,
       * @param contractno - the contract's number,
       * @param adminacc - account of the administrator,
       * @param issuer - the issuer,
       * @param issuerurl - the url of issuer,
       * @param issuerid - the id of issuer,
       * @param issueradd - address of issuer,
       * @param issuertel - telephone of issuer,
       * @param regacc - account of the register,
       * @param memo - the memo string.
       */
      [[eosio::action]]
      void regtoken( const name&    manager,
                     const string&  tknsymstr,
                     uint8_t        digit,
                     const string&  tokenname,
                     const string&  issuechain,
                     const name&    contractacc,
                     const string&  contractname,
                     uint32_t       contractno,
                     const name&    adminacc,
                     const name&    issuer,
                     const string&  issuerurl,
                     const string&  issuerid,
                     const string&  issueradd,
                     const string&  issuertel,
                     const name     regacc,
                     const string&  memo );

      /**
       * Modify one YottaChain's token.
       *
       * @param modifier - which account performs this action,
       * @param tknsymstr - token symbol string,
       * @param digit - decimal digit
       * @param tokenname - token name,
       * @param issuechain - issue in which chain,
       * @param contractacc - account for the deployment contract,
       * @param contractname - the contract's name,
       * @param contractno - the contract's number,
       * @param adminacc - account of the administrator,
       * @param issuer - the issuer,
       * @param issuerurl - the url of issuer,
       * @param issuerid - the id of issuer,
       * @param issueradd - address of issuer,
       * @param issuertel - telephone of issuer,
       * @param regacc - account of the register,
       * @param memo - the memo string.
       */
      [[eosio::action]]
      void modtoken( const name&    modifier,
                     const string&  tknsymstr,
                     uint8_t        digit,
                     const string&  tokenname,
                     const string&  issuechain,
                     const name&    contractacc,
                     const string&  contractname,
                     uint32_t       contractno,
                     const name&    adminacc,
                     const name&    issuer,
                     const string&  issuerurl,
                     const string&  issuerid,
                     const string&  issueradd,
                     const string&  issuertel,
                     const name     regacc,
                     const string&  memo );

      /**
       * Remove one YottaChain's token.
       *
       * @param manager - which account performs this action,
       * @param tknsymstr - token symbol string,
       * @param digit - decimal digit,
       * @param memo - the memo string.
       */
      [[eosio::action]]
      void rmvtoken( const name&    manager,
                     const string&  tknsymstr,
                     uint8_t        digit,
                     const string&  memo );

      /**
       * Set the supply and max_supply of one YottaChain's token.
       *
       * @param manager - which account performs this action,
       * @param tknsymstr - token symbol string,
       * @param digit - decimal digit,
       * @param memo - the memo string.
       */
      [[eosio::action]]
      void setsupply( const name&    manager,
                      const string&  tknsymstr,
                      uint8_t        digit,
                      const asset&   supply,
                      const asset&   max_supply,
                      const string&  memo );

      /**
       * Set the fee of registering one YottaChain's token.
       *
       * @param reg_fee - register token fee.
       */
      [[eosio::action]]
      void setregfee( const asset& reg_fee );

      /**
       * Allows `from` account to transfer to `to` account the `quantity` tokens.
       * One account is debited and the other is credited with quantity tokens.
       *
       * @param from - transfer from which account,
       * @param to - transfer to which account,
       * @param quantity - the quantity of tokens to be transferred,
       * @param memo - the memo string to accompany the transaction.
       */
      [[eosio::action]]
      void transfer( const name&    from,
                     const name&    to,
                     const asset&   quantity,
                     const string&  memo );

      /**
       * Increase the count.
       *
       * @param creater - the account which create a new token,
       * @param memo - the memo string.
       */
      [[eosio::action]]
      void addcount( const name&    creater,
                     const string&  memo );
      
      /**
       * Simply register one YottaChain's token.
       *
       * @param manager - the manager account,
       * @param issuer - the issuer,
       * @param maximum_supply - the maximum supply,
       * @param tokenname - token name,
       * @param memo - the memo string.
       */
      [[eosio::action]]
      void simreg( const name&    manager,
                   const name&    issuer,
                   const asset&   maximum_supply,
                   const string&  tokenname,
                   const string&  memo );

      /**
       * Update one token's supply.
       *
       * @param mngtype - manager type
       * @param manager - the manager account,
       * @param contractacc - the account for the deployment contract,
       * @param supply - token supply,
       */
      [[eosio::action]]
      void updatesupply( uint8_t mngtype,
                         const name&    manager,
                         const name&    contractacc,
                         const asset&   supply );

      using addaccmng_action = eosio::action_wrapper<"addaccmng"_n, &tokenreg::addaccmng>;
      using rmvaccmng_action = eosio::action_wrapper<"rmvaccmng"_n, &tokenreg::rmvaccmng>;
      using keyreg_action = eosio::action_wrapper<"keyreg"_n, &tokenreg::keyreg>;
      using regtoken_action = eosio::action_wrapper<"regtoken"_n, &tokenreg::regtoken>;
      using modtoken_action = eosio::action_wrapper<"modtoken"_n, &tokenreg::modtoken>;
      using rmvtoken_action = eosio::action_wrapper<"rmvtoken"_n, &tokenreg::rmvtoken>;
      using setsupply_action = eosio::action_wrapper<"setsupply"_n, &tokenreg::setsupply>;
      using setregfee_action = eosio::action_wrapper<"setregfee"_n, &tokenreg::setregfee>;
      using transfer_action = eosio::action_wrapper<"transfer"_n, &tokenreg::transfer>;
      using addcount_action = eosio::action_wrapper<"addcount"_n, &tokenreg::addcount>;
      using simreg_action = eosio::action_wrapper<"simreg"_n, &tokenreg::simreg>;
      using updatesupply_action = eosio::action_wrapper<"updatesupply"_n, &tokenreg::updatesupply>;

   private:
      struct [[eosio::table]] accmng {
         name     manager;

         uint64_t primary_key()const { return manager.value; }
      };
      typedef eosio::multi_index< "accmng"_n, accmng> accmngs;

      struct [[eosio::table]] tokeninfo {
         uint32_t    tokenno;
         string      tokenname;
         string      issuechain; //issue in which chain
         name        contractacc; //account for the deployment contract
         string      contractname;
         string      contractadd;//合约地址
         uint32_t    contractno;
         name        adminacc; //account of the administrator
         name        issuer;
         string      issuerurl;//发行者官网
         string      issuerid;
         string      issueradd;
         string      issuertel;
         uint16_t    precision;//小数精度位数
         asset       supply;
         asset       max_supply;
         name        regacc; //account of the register
         uint64_t    regtime; //regist time
         uint64_t    updatetime;
         string      memo;

         uint64_t primary_key()const { return max_supply.symbol.code().raw(); }
         uint64_t get_issuer() const { return issuer.value; }
         uint64_t get_tokenno() const { return (uint64_t)tokenno; }

         /*EOSLIB_SERIALIZE( tokeninfo, (tokenno)(tokensym)(tokenname)(issuechain)(contractacc)(contractname)(contractno)(adminacc)
                           (issuer)(issuerurl)(issuerid)(issueradd)(issuertel)
                           (supply)(max_supply)(regacc)(regtime)(updatetime)(memo) )*/
      };
      typedef eosio::multi_index< "tokeninfo"_n, tokeninfo,
                                  eosio::indexed_by< "issuer"_n, eosio::const_mem_fun<tokeninfo, uint64_t, &tokeninfo::get_issuer> >,
                                  eosio::indexed_by< "tokenno"_n, eosio::const_mem_fun<tokeninfo, uint64_t, &tokeninfo::get_tokenno> >
                                > tokeninfos;

      struct [[eosio::table]] reginfo {
         uint32_t    next_tokenno;
         uint32_t    tokens_count;
      };
      typedef eosio::singleton<"reginfo"_n, reginfo> reginfo_singleton;

      struct [[eosio::table]] regfee {
         asset  reg_fee;
      };
      typedef eosio::singleton<"regfee"_n, regfee> regfee_singleton;

      struct [[eosio::table]] userreg {
         name        user;
         uint32_t    reg_count;
         uint32_t    total_count;
         uint32_t    next_tokenno;

         uint64_t primary_key()const { return user.value; }
      };
      typedef eosio::multi_index< "userreg"_n, userreg> userregs;

      struct [[eosio::table]] currency_stat {
         asset    supply;
         asset    max_supply;
         name     issuer;
         //name     ruler;
         name     poolsetter;
         name     unlocker;
         uint64_t time = 0; //exchanging time
         uint32_t tokenno; //token number

         uint64_t primary_key()const { return max_supply.symbol.code().raw(); }
      };
      typedef eosio::multi_index< "stat"_n, currency_stat > stats;

};

extern "C" {
   void apply( uint64_t receiver, uint64_t code, uint64_t action) {
      /*if ( receiver == code && action == name("setassetinfo").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( staking, (setassetinfo) );
         }
      }
      if ( receiver == code && action == name("setstake").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( staking, (setstake) );
         }
      }
      if ( receiver == code && action == name("setexplain").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( staking, (setexplain) );
         }
      }*/
      if ( receiver == code && action == name("addaccmng").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( tokenreg, (addaccmng) );
         }
      }
      if ( receiver == code && action == name("setregfee").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( tokenreg, (setregfee) );
         }
      }
      if (code == name("eosio.token").value && action == name("transfer").value) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( tokenreg, (transfer) );
         }
      }
      if ( receiver == code && action == name("addcount").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( tokenreg, (addcount) );
         }
      }
      if ( receiver == code && action == name("simreg").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( tokenreg, (simreg) );
         }
      }
      if ( receiver == code && action == name("updatesupply").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( tokenreg, (updatesupply) );
         }
      }
      /*
      if (code == name("ysr.ystar").value && action == name("yrctransfer").value) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( staking, (yrctransfer) );
         }
      }
      if ( receiver == code && action == name("getprincipal").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( staking, (getprincipal) );
         }
      }
      if ( receiver == code && action == name("getinterest").value ) {
         switch( action ) {
            EOSIO_DISPATCH_HELPER( staking, (getinterest) );
         }
      }*/
   }
}
