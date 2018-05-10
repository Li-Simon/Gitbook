# 第一节 比特币代码分析

Validation.cpp  
BTC 基本类

[https://en.bitcoin.it/wiki/Dump\_format](https://en.bitcoin.it/wiki/Dump_format)

```
class COutPoint
{
public:
    uint256 hash;  //
    uint32_t n;
}
COutPoint(000000, -1)
Part of a CTxIn structure, this references a specific output. The first value is the 
truncated hash of the transaction, and the second value is an output index.
```

```
class CTxIn
{
public:
    COutPoint prevout;
    CScript scriptSig;
    uint32_t nSequence;
    CScriptWitness scriptWitness; //! Only serialized through CTransaction
}
CTxIn(COutPoint(237fe8, 0), scriptSig=0xA87C02384E1F184B79C6AC)
CTxIn(COutPoint(000000, -1), coinbase 04ffff001d010)
CTxIn(COutPoint(237fe8, 0), scriptSig=0xA87C02384E1F184B79C6AC, nSequence=5000)
A transaction input. 
scriptSig is the truncated scriptSig of the input. "coinbase" is the non-truncated scriptSig of a generation input. 
nSequence appears only if the input has a non-default sequence. 
Sequence numbers are intended for use with the transaction replacement feature, but can currently be safely ignored.
```

```
class CTxOut
{
public:
    CAmount nValue;
    CScript scriptPubKey;
}
```



