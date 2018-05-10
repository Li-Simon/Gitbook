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
class CBlock : public CBlockHeader
{
public:
    // network and disk
    std::vector<CTransactionRef> vtx;
}
CBlock(hash=00000000009ffdadbb2a, ver=1, hashPrevBlock=0000000000b079382c19, hashMerkleRoot=e81287,
nTime=1281156783, nBits=1c00ba18, nNonce=2283211008, vtx=6)
  CTransaction(hash=2d7f4d, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(000000, -1), coinbase 0418ba001c02ce03)
    CTxOut(nValue=50.00000000, scriptPubKey=0x4FE11D72F988AEA611F026)
  CTransaction(hash=3407a8, ver=1, vin.size=2, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(df39bf, 0), scriptSig=0x01DD1AD8E9EFE65B70E983)
    CTxIn(COutPoint(64ebea, 1), scriptSig=0x0165A1F9873BA16265D9C4)
    CTxOut(nValue=0.06000000, scriptPubKey=OP_DUP OP_HASH160 0xEDEF)
  CTransaction(hash=5edf5a, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(b77e0f, 0), scriptSig=0x01E39C53AFC1B9BE02E53A)
    CTxOut(nValue=350.00000000, scriptPubKey=OP_DUP OP_HASH160 0xD7EF)
  CTransaction(hash=65c356, ver=1, vin.size=1, vout.size=2, nLockTime=0)
    CTxIn(COutPoint(893335, 0), scriptSig=0x01B8C315FD58F0DFA0DEA2)
    CTxOut(nValue=1.85850000, scriptPubKey=OP_DUP OP_HASH160 0x3181)
    CTxOut(nValue=3.14150000, scriptPubKey=OP_DUP OP_HASH160 0xF99E)
  CTransaction(hash=89aa32, ver=1, vin.size=1, vout.size=2, nLockTime=0)
    CTxIn(COutPoint(4a7469, 0), scriptSig=0x010D15199DCE4B11D391CF)
    CTxOut(nValue=0.05000000, scriptPubKey=OP_DUP OP_HASH160 0x5603)
    CTxOut(nValue=0.20000000, scriptPubKey=OP_DUP OP_HASH160 0x6074)
  CTransaction(hash=e3e69c, ver=1, vin.size=1, vout.size=2, nLockTime=0)
    CTxIn(COutPoint(b77e0f, 1), scriptSig=0x012E18AF1264180255E0C3)
    CTxOut(nValue=50.00000000, scriptPubKey=OP_DUP OP_HASH160 0x458E)
    CTxOut(nValue=100.00000000, scriptPubKey=OP_DUP OP_HASH160 0x9EEF)
  vMerkleTree: 2d7f4d 3407a8 5edf5a 65c356 89aa32 e3e69c 8ebc6a d5e414 89b77c d1074c 70a4e6 e81287
  
  A block. Hash is the truncated hash. Version is the block version. 
  HashPrevBlock is the truncated hash of the previous block. 
  HashMerkleRoot is the truncated Merkle root. nTime is the Unix timestamp of the block. 
  nBits is the current target in compact format. nNonce is the nonce. 
  vtx is the number of transactions.
```



