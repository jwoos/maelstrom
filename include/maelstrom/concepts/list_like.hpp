
// TODO flesh out
template <typename T>
concept list_like = requires(T) {
	T::size;
};
