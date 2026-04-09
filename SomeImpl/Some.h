#pragma once
#include <memory>

class SomeImpl;

class Some {
	std::unique_ptr<SomeImpl> pimpl_;

	const SomeImpl* GetPimpl() const {
		return pimpl_.get();
	}

	SomeImpl* GetPimpl() {
		return pimpl_.get();
	}
	
public:
	int Do(size_t i) const;
	int& Do(size_t i);

	Some();
	Some(Some&& rhs) = default;
	Some(const Some& rhs);
	~Some();
};