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
CTxOut(nValue=50.00000000, scriptPubKey=OP_DUP OP_HASH160 0x1512)
A transaction output. 
nValue is the the full-precision output value. 
scriptPubKey is the truncated CScript for the output (the entire script string is truncated to 30 characters).
```

```
class CTransaction
{
public:
    const int32_t nVersion;
    const std::vector<CTxIn> vin;
    const std::vector<CTxOut> vout;
    const uint32_t nLockTime;
private:
    /** Memory only. */
    const uint256 hash;
}
CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
CTxIn(COutPoint(000000, -1), coinbase 04ffff001d010)
CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
A transaction. hash is the truncated hash. ver is the transaction version.
vout.size is the number of outputs. 
nLockTime is intended for use with transaction replacement, and is not currently used for anything useful.

```

```
class CBlockHeader
{
public:
    // header
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;
}
```



