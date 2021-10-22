#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include <vector>

//Vector Tree!
template <typename E>
class VectorCompleteTree
{

private:
  std::vector<E> V; 
public:
  typedef typename std::vector<E>::iterator Position;

protected:
  Position pos(int i) 
  {
    return V.begin() + i;
  }

  int idx(const Position &p) const
  {
    return p - V.begin();
  }

public:
  //dang he defines all the stuff right here in these few lines
  //Don't gotta worry too much, just know this is a tree made using an index
  VectorCompleteTree() : V(1) {}
  int size() const { return V.size() - 1; }
  Position left(const Position &p) { return pos(2 * idx(p)); }
  Position right(const Position &p) { return pos(2 * idx(p) + 1); }
  Position parent(const Position &p) { return pos(idx(p) / 2); }
  bool hasLeft(const Position &p) const { return 2 * idx(p) <= size(); }
  bool hasRight(const Position &p) const { return 2 * idx(p) + 1 <= size(); }
  bool isRoot(const Position &p) const { return idx(p) == 1; }
  Position root() { return pos(1); }
  Position last() { return pos(size()); }
  void addLast(const E &e) { V.push_back(e); }
  void removeLast() { V.pop_back(); }
  void swap(const Position &p, const Position &q)
  {
    E e = *q;
    *q = *p;
    *p = e;
  }
};

//C == comparator
template <typename E, typename C>
class HeapQueue
{
public:
  int size() const;
  bool empty() const;
  void insert(const E &e);
  const E &min();
  void removeMin();

private:
  //looks like this heap is implemented using a vector
  //T = Vector Tree
  VectorCompleteTree<E> T;
  C isLess;

  typedef typename VectorCompleteTree<E>::Position Position;
};

//return size of the vector tree
template <typename E, typename C>
int HeapQueue<E, C>::size() const
{
  return T.size();
}

//if the size == 0 then the tree is empty
template <typename E, typename C>
bool HeapQueue<E, C>::empty() const
{
  return size() == 0;
}

//Oh, we're doing a minimum heap?
template <typename E, typename C>
const E &HeapQueue<E, C>::min()
{
  return *(T.root());
}

//do the swapperooni with the root
template <typename E, typename C>
void HeapQueue<E, C>::removeMin()
{
  if (size() == 1)
  {
    T.removeLast();
  }
  else
  {
    Position u = T.root();
    T.swap(u, T.last());
    T.removeLast();

    while (T.hasLeft(u))
    {
      Position v = T.left(u);
      if (T.hasRight(u) && isLess(*(T.right(u)), *v))
      {
        v = T.right(u);
      }
      if (isLess(*v, *u))
      {
        T.swap(u, v);
        u = v;
      }
      else
      {
        break;
      }
    }
  }
}

//add to the end, then percolate back up
template <typename E, typename C>
void HeapQueue<E, C>::insert(const E &e)
{
  T.addLast(e);
  Position v = T.last();
  while (!T.isRoot(v))
  {
    Position u = T.parent(v);
    if (!isLess(*v, *u))
      break;
    T.swap(v, u);
    v = u;
  }
}


#endif