// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.


#ifndef MYHASH
#define MYHASH

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
    struct Node
    {
        KeyType   key;
        ValueType value;
        Node *    next;
        Node();
    };

    Node ** hashTable;
    int numBuckets;
    int numItems;
    double maxLoadFactor = 0.5;

    int getBucketNumber(const KeyType & key) const; //gets position of bucket with key
    void init(); //initializes and sets up hashTable
    void clearTable(); //clears the table and assosciate memory
    void resize(); //takes care of resizing the hash table
    void insert(int pos, const KeyType& key, const ValueType& value);//insert a new key, value pair at a bucket position
};

#endif // MYHASH_INCLUDED

template <class KeyType, class ValueType>
MyHash<KeyType, ValueType>::Node::Node()
{
    next = nullptr;
}

template <class KeyType, class ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor): numItems(0), numBuckets(100), maxLoadFactor(maxLoadFactor)
{
    if(maxLoadFactor <= 0)
        this->maxLoadFactor = 0.5;
    else if(maxLoadFactor > 2)
        this->maxLoadFactor = 2;
    init();
};

template<class KeyType, class ValueType>
void MyHash<KeyType, ValueType>::clearTable()
{
    Node * current = nullptr;
    Node * next = nullptr;

    //delete all the Nodes in hashTable
    for(int i = 0; i < numBuckets; i++)
    {
        current = hashTable[i];
        while(current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    delete [] hashTable;
}

template<class KeyType, class ValueType>
void MyHash<KeyType, ValueType>::init()
{
    //set up hashTable and set its buckets to nullptr
    hashTable = new Node * [numBuckets];

    numItems = 0;

    for(int i = 0; i < numBuckets; i++)
        hashTable[i] = nullptr;
};

template <class KeyType, class ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    clearTable();
};

template <class KeyType, class ValueType>
int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType & key) const
{
    unsigned int hash(const KeyType & key);

    //get bucket number by using the <functional> hash functions and apply the modulus operator
    int h = hash(key) % numBuckets;
    return h;
};

template <class KeyType, class ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    clearTable();
    numBuckets = 100;
    init();
};

template <class KeyType, class ValueType>
void MyHash<KeyType, ValueType>::insert(int pos, const KeyType& key, const ValueType& value)
{
    Node * current = hashTable[pos];
    bool exists = false;

    //if current bucket is nullptr, add a new Node at the position
    if(current == nullptr)
    {
        Node * node = new Node;
        node->key = key;
        node->value = value;
        node->next = nullptr;
        hashTable[pos] = node;
        numItems++;
    }
    else
    {
        //else add a new Node to the end of the last Node in the bucket and link them together
        Node * prev;
        while(current != nullptr)
        {
            if(current->key == key)
            {
                current->value = value;
                exists = true;
                break;
            }
            prev = current;
            current = current->next;
        }

        //only add it, if it does not already exist
        if(!exists)
        {
            Node * node = new Node;
            node->key = key;
            node->value = value;
            node->next = nullptr;
            prev->next = node;
            numItems++;
        }
    }
};

template <class KeyType, class ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    insert(getBucketNumber(key), key, value);

    if(getLoadFactor() > maxLoadFactor) //resize if the load factor is too big
        resize();
};

template <class KeyType, class ValueType>
void MyHash<KeyType, ValueType>::resize()
{
    Node ** tempTable = hashTable; //Point tempTable to current hashTable
    numBuckets = 2*numBuckets;
    init(); //Reset the current hashTable with new bucket size

    Node * current = nullptr;

    //insert all the Nodes in the old hashTable to the current one with new bucket numbers
    for(int i = 0; i < numBuckets/2; i++)
    {
        current = tempTable[i];
        while(current != nullptr)
        {
            insert(getBucketNumber(current->key), current->key, current->value);
            current = current->next;
        }
    }

    current = nullptr;
    Node * next = nullptr;

    //Free memory associated with the old hashTable
    for(int i = 0; i < numBuckets/2; i++)
    {
        current = tempTable[i];
        while(current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    delete  [] tempTable;
};

template <class KeyType, class ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return numItems;
};

template <class KeyType, class ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return numItems/(1.0 * numBuckets);
};

template <class KeyType, class ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    int h = getBucketNumber(key);
    Node * current = hashTable[h];

    while(current != nullptr)
    {
        if(current->key == key)
            return &(current->value);

        current = current->next;
    }

    return nullptr;
};

