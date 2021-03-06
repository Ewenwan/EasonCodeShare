// GridZeroInitialized.h

template <typename T>
class Grid
{
public:
	Grid(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
	Grid(const Grid<T>& src);
	virtual ~Grid();
	Grid<T>& operator=(const Grid<T>& rhs);

	void setElementAt(size_t x, size_t y, const T& inElem);
	T& getElementAt(size_t x, size_t y);
	const T& getElementAt(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }
	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

protected:
	void copyFrom(const Grid<T>& src);
	T** mCells;
	size_t mWidth, mHeight;
};

template <typename T>
Grid<T>::Grid(size_t inWidth, size_t inHeight) : mWidth(inWidth), mHeight(inHeight)
{
	mCells = new T* [mWidth];
	for (size_t i = 0; i < mWidth; i++) {
		mCells[i] = new T[mHeight];
		for (size_t j = 0; j < mHeight; j++) {
			mCells[i][j] = T();
		}
	}
}

template <typename T>
Grid<T>::Grid(const Grid<T>& src)
{
	copyFrom(src);
}

template <typename T>
Grid<T>::~Grid()
{
	// free the old memory
	for (size_t i = 0; i < mWidth; i++) {
		delete [] mCells[i];
	}
	delete [] mCells;
	mCells = nullptr;
}

template <typename T>
void Grid<T>::copyFrom(const Grid<T>& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;

	mCells = new T* [mWidth];
	for (size_t i = 0; i < mWidth; i++) {
		mCells[i] = new T[mHeight];
	}

	for (size_t i = 0; i < mWidth; i++) {
		for (size_t j = 0; j < mHeight; j++) {
			mCells[i][j] = src.mCells[i][j];
		}
	}
}

template <typename T>
Grid<T>& Grid<T>::operator=(const Grid<T>& rhs)
{
	// check for self-assignment
	if (this == &rhs) {
		return *this;
	}
	// free the old memory
	for (size_t i = 0; i < mWidth; i++) {
		delete [] mCells[i];
	}
	delete [] mCells;
	mCells = nullptr;

	// copy the new memory
	copyFrom(rhs);

	return *this;
}

template <typename T>
void Grid<T>::setElementAt(size_t x, size_t y, const T& inElem)
{
	mCells[x][y] = inElem;
}

template <typename T>
T& Grid<T>::getElementAt(size_t x, size_t y)
{
	return mCells[x][y];
}

template <typename T>
const T& Grid<T>::getElementAt(size_t x, size_t y) const
{
	return mCells[x][y];
}
