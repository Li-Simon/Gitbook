# 第一节 比特币代码分析

Validation.cpp  
BTC 基本类

[https://en.bitcoin.it/wiki/Dump\_format](https://en.bitcoin.it/wiki/Dump_format)

[https://en.bitcoin.it/wiki/Bitcoin\_Core\_0.11\_\(ch\_6\):\_The\_Blockchain](https://en.bitcoin.it/wiki/Bitcoin_Core_0.11_%28ch_6%29:_The_Blockchain)

[https://bitcointalk.to/index.php?topic=1641447.0](https://bitcointalk.to/index.php?topic=1641447.0)

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

```
class CChain {
private:
    std::vector<CBlockIndex*> vChain;
}
```

```
/** The block chain is a tree shaped structure starting with the
 * genesis block at the root, with each block potentially having multiple
 * candidates to be the next block. A blockindex may have multiple pprev pointing
 * to it, but at most one of them can be part of the currently active branch.
class CBlockIndex
{
public:
    //! pointer to the hash of the block, if any. Memory is owned by this CBlockIndex
    const uint256* phashBlock;

    //! pointer to the index of the predecessor of this block
    CBlockIndex* pprev;

    //! pointer to the index of some further predecessor of this block
    CBlockIndex* pskip;

    //! height of the entry in the chain. The genesis block has height 0
    int nHeight;

    //! Which # file this block is stored in (blk?????.dat)
    int nFile;

    //! Byte offset within blk?????.dat where this block's data is stored
    unsigned int nDataPos;

    //! Byte offset within rev?????.dat where this block's undo data is stored
    unsigned int nUndoPos;

    //! (memory only) Total amount of work (expected number of hashes) in the chain up to and including this block
    arith_uint256 nChainWork;

    //! Number of transactions in this block.
    //! Note: in a potential headers-first mode, this number cannot be relied upon
    unsigned int nTx;

    //! (memory only) Number of transactions in the chain up to and including this block.
    //! This value will be non-zero only if and only if transactions for this block and all its parents are available.
    //! Change to 64-bit type when necessary; won't happen before 2030
    unsigned int nChainTx;

    //! Verification status of this block. See enum BlockStatus
    unsigned int nStatus;

    //! block header
    int nVersion;
    uint256 hashMerkleRoot;
    unsigned int nTime;
    unsigned int nBits;
    unsigned int nNonce;

    //! (memory only) Sequential id assigned to distinguish order in which blocks are received.
    int32_t nSequenceId;

    //! (memory only) Maximum nTime in the chain upto and including this block.
    unsigned int nTimeMax;
}
```

```
class CNodeStats
{
public:
    NodeId nodeid;
    ServiceFlags nServices;
    bool fRelayTxes;
    int64_t nLastSend;
    int64_t nLastRecv;
    int64_t nTimeConnected;
    int64_t nTimeOffset;
    std::string addrName;
    int nVersion;
    std::string cleanSubVer;
    bool fInbound;
    bool fAddnode;
    int nStartingHeight;
    uint64_t nSendBytes;
    mapMsgCmdSize mapSendBytesPerMsgCmd;
    uint64_t nRecvBytes;
    mapMsgCmdSize mapRecvBytesPerMsgCmd;
    bool fWhitelisted;
    double dPingTime;
    double dPingWait;
    double dMinPing;
    std::string addrLocal;
    CAddress addr;
};
```

```
/** 
 * A CWallet is an extension of a keystore, which also maintains a set of transactions and balances,
 * and provides the ability to create new transactions.
 */
class CWallet : public CCryptoKeyStore, public CValidationInterface
{
private:
    static std::atomic<bool> fFlushThreadRunning;
    CWalletDB *m_pwalletdbEncryption;

    //! the current wallet version: clients below this version are not able to load the wallet
    int m_nWalletVersion;

    //! the maximum wallet format version: memory-only variable that specifies to what version this wallet may be upgraded
    int m_nWalletMaxVersion;

    int64_t nNextResend;
    int64_t nLastResend;
    bool fBroadcastTransactions;
    TxSpends mapTxSpends;
    void AddToSpends(const COutPoint& outpoint, const uint256& wtxid);
    void AddToSpends(const uint256& wtxid);

    /* Mark a transaction (and its in-wallet descendants) as conflicting with a particular block. */
    void MarkConflicted(const uint256& hashBlock, const uint256& hashTx);

    void SyncMetaData(std::pair<TxSpends::iterator, TxSpends::iterator>);

    /* the HD chain data model (external chain counters) */
    CHDChain m_hdChain;

    bool m_fFileBacked;

    std::set<int64_t> setKeyPool;
    static CFeeRate minTxFee;
    static CFeeRate fallbackFee;

    void SetNull()
    {
        m_nWalletVersion = FEATURE_BASE;
        m_nWalletMaxVersion = FEATURE_BASE;
        m_fFileBacked = false;
        nMasterKeyMaxID = 0;
        m_pwalletdbEncryption = NULL;
        nOrderPosNext = 0;
        nNextResend = 0;
        nLastResend = 0;
        nTimeFirstKey = 0;
        fBroadcastTransactions = false;
    }
}
```

```
class CValidationInterface {
protected:
    virtual void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) {}
    virtual void SyncTransaction(const CTransaction &tx, const CBlockIndex *pindex, int posInBlock) {}
    virtual void SetBestChain(const CBlockLocator &locator) {}
    virtual void UpdatedTransaction(const uint256 &hash) {}
    virtual void Inventory(const uint256 &hash) {}
    virtual void ResendWalletTransactions(int64_t nBestBlockTime, CConnman* connman) {}
    virtual void BlockChecked(const CBlock&, const CValidationState&) {}
    virtual void GetScriptForMining(boost::shared_ptr<CReserveScript>&) {};
    virtual void ResetRequestCount(const uint256 &hash) {};
    virtual void NewPoWValidBlock(const CBlockIndex *pindex, const std::shared_ptr<const CBlock>& block) {};
    friend void ::RegisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterAllValidationInterfaces();
};
```

```
/** Keystore which keeps the private keys encrypted.
 * It derives from the basic key store, which is used if no encryption is active.
 */
class CCryptoKeyStore : public CBasicKeyStore
{
private:
    CryptedKeyMap mapCryptedKeys;

    CKeyingMaterial vMasterKey;

    //! if fUseCrypto is true, mapKeys must be empty
    //! if fUseCrypto is false, vMasterKey must be empty
    bool fUseCrypto;

    //! keeps track of whether Unlock has run a thorough check before
    bool fDecryptionThoroughlyChecked;

protected:
    bool SetCrypted();

    //! will encrypt previously unencrypted keys
    bool EncryptKeys(CKeyingMaterial& vMasterKeyIn);

    bool Unlock(const CKeyingMaterial& vMasterKeyIn);
}
```

```
/** Basic key store, that keeps keys in an address->secret map */
class CBasicKeyStore : public CKeyStore
{
protected:
    KeyMap mapKeys;
    WatchKeyMap mapWatchKeys;
    ScriptMap mapScripts;
    WatchOnlySet setWatchOnly;
}
```

```
/** A virtual base class for key stores */
class CKeyStore
{
protected:
    mutable CCriticalSection cs_KeyStore;

public:
    virtual ~CKeyStore() {}

    //! Add a key to the store.
    virtual bool AddKeyPubKey(const CKey &key, const CPubKey &pubkey) =0;
    virtual bool AddKey(const CKey &key);

    //! Check whether a key corresponding to a given address is present in the store.
    virtual bool HaveKey(const CKeyID &address) const =0;
    virtual bool GetKey(const CKeyID &address, CKey& keyOut) const =0;
    virtual void GetKeys(std::set<CKeyID> &setAddress) const =0;
    virtual bool GetPubKey(const CKeyID &address, CPubKey& vchPubKeyOut) const =0;

    //! Support for BIP 0013 : see https://github.com/bitcoin/bips/blob/master/bip-0013.mediawiki
    virtual bool AddCScript(const CScript& redeemScript) =0;
    virtual bool HaveCScript(const CScriptID &hash) const =0;
    virtual bool GetCScript(const CScriptID &hash, CScript& redeemScriptOut) const =0;

    //! Support for Watch-only addresses
    virtual bool AddWatchOnly(const CScript &dest) =0;
    virtual bool RemoveWatchOnly(const CScript &dest) =0;
    virtual bool HaveWatchOnly(const CScript &dest) const =0;
    virtual bool HaveWatchOnly() const =0;
};
```



