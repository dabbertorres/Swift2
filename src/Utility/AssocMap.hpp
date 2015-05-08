#ifndef ASSOC_MAP_HPP
#define ASSOC_MAP_HPP

#include <vector>
#include <unordered_map>

namespace swift
{
	namespace util
	{
		template<typename K, typename V>
		class AssocMap
		{
			private:
				using Keys = typename std::unordered_map<K, typename std::vector<V>::iterator>;
				using Data = typename std::vector<V>;
			
			public:
				AssocMap() = default;
				AssocMap(std::size_t size);
				~AssocMap() = default;

				/* usings */
				using iterator = typename Keys::iterator;
				using const_iterator = typename Keys::const_iterator;
				
				using data_iterator = typename Data::iterator;
				using data_const_iterator = typename Data::const_iterator;
				
				using pair = typename std::pair<K, V>;

				/* iterators */
				iterator key_begin() noexcept;
				const_iterator key_begin() const noexcept;
				iterator key_end() noexcept;
				const_iterator key_end() const noexcept;

				const_iterator key_cbegin() const noexcept;
				const_iterator key_cend() const noexcept;
				
				data_iterator data_begin() noexcept;
				data_const_iterator data_begin() const noexcept;
				data_iterator data_end() noexcept;
				data_const_iterator data_end() const noexcept;

				data_const_iterator data_cbegin() const noexcept;
				data_const_iterator data_cend() const noexcept;
				
				data_iterator (&begin)() = data_begin;
				data_iterator (&end)() = data_end;
				data_const_iterator (&cbegin)() = data_cbegin;
				data_const_iterator (&cend)() = data_cend;

				/* capacity */
				bool empty() const noexcept;
				std::size_t size() const noexcept;
				std::size_t max_size() const noexcept;
				void reserve(std::size_t n);

				/* access */
				V& operator[](const K& k);
				V& operator[](K&& k);
				V& at(const K& k);
				const V& at(const K& k) const;

				/* lookup */
				iterator find(const K& k);
				const_iterator find(const K& k) const;

				/* modifiers */
				template<typename... Args>
				std::pair<V&, bool> emplace(const K& k, Args&&... args);

				std::size_t erase(const K& k);
				iterator erase(const_iterator position);
				iterator erase(const_iterator first, const_iterator last);
				void clear() noexcept;

			private:
				Data data;
				Keys keys;
		};

		template<typename K, typename V>
		bool operator==(const AssocMap<K, V>& lhs, const AssocMap<K, V>& rhs);

		template<typename K, typename V>
		bool operator!=(const AssocMap<K, V>& lhs, const AssocMap<K, V>& rhs);

		/* implementation */
		template<typename K, typename V>
		AssocMap<K, V>::AssocMap(std::size_t size)
		{
			data.reserve(size);
			keys.reserve(size);
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::iterator AssocMap<K, V>::key_begin() noexcept
		{
			return keys.begin();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::const_iterator AssocMap<K, V>::key_begin() const noexcept
		{
			return keys.begin();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::iterator AssocMap<K, V>::key_end() noexcept
		{
			return keys.end();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::const_iterator AssocMap<K, V>::key_end() const noexcept
		{
			return keys.end();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::const_iterator AssocMap<K, V>::key_cbegin() const noexcept
		{
			return keys.cbegin();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::const_iterator AssocMap<K, V>::key_cend() const noexcept
		{
			return keys.cend();
		}
		
		template<typename K, typename V>
		typename AssocMap<K, V>::data_iterator AssocMap<K, V>::data_begin() noexcept
		{
			return data.begin();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::data_const_iterator AssocMap<K, V>::data_begin() const noexcept
		{
			return data.begin();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::data_iterator AssocMap<K, V>::data_end() noexcept
		{
			return data.end();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::data_const_iterator AssocMap<K, V>::data_end() const noexcept
		{
			return data.end();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::data_const_iterator AssocMap<K, V>::data_cbegin() const noexcept
		{
			return data.cbegin();
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::data_const_iterator AssocMap<K, V>::data_cend() const noexcept
		{
			return data.cend();
		}

		template<typename K, typename V>
		bool AssocMap<K, V>::empty() const noexcept
		{
			return keys.empty();
		}

		template<typename K, typename V>
		std::size_t AssocMap<K, V>::size() const noexcept
		{
			return keys.size();
		}

		template<typename K, typename V>
		std::size_t AssocMap<K, V>::max_size() const noexcept
		{
			return keys.max_size();
		}

		template<typename K, typename V>
		void AssocMap<K, V>::reserve(std::size_t n)
		{
			data.reserve(n);
			keys.reserve(n);
		}

		template<typename K, typename V>
		V& AssocMap<K, V>::operator[](const K& k)
		{
			return *keys[k];
		}

		template<typename K, typename V>
		V& AssocMap<K, V>::operator[](K&& k)
		{
			return *keys[k];
		}

		template<typename K, typename V>
		V& AssocMap<K, V>::at(const K& k)
		{
			return *keys.at(k);
		}

		template<typename K, typename V>
		const V& AssocMap<K, V>::at(const K& k) const
		{
			return *keys.at(k);
		}

		template<typename K, typename V>
		typename AssocMap<K, V>::iterator AssocMap<K, V>::find(const K& k)
		{
			return keys.find(k);
		}
		
		template<typename K, typename V>
		typename AssocMap<K, V>::const_iterator AssocMap<K, V>::find(const K& k) const
		{
			return keys.find(k);
		}

		template<typename K, typename V>
		template<typename... Args>
		std::pair<V&, bool> AssocMap<K, V>::emplace(const K& k, Args&&... args)
		{
			data.emplace_back(std::forward<Args>(args)...);
			auto lastIt = data.end() - 1;
			auto result = keys.emplace(k, lastIt);
			
			if(!result.second)
				data.erase(lastIt);
				
			return {data.back(), result.second};
		}
		
		template<typename K, typename V>
		std::size_t AssocMap<K, V>::erase(const K& k)
		{
			data.erase(keys.at(k));
			return keys.erase(k);
		}
		
		template<typename K, typename V>
		typename AssocMap<K, V>::iterator AssocMap<K, V>::erase(typename AssocMap<K, V>::const_iterator position)
		{
			data.erase(keys.at(position));
			return keys.erase(position);
		}
		
		template<typename K, typename V>
		typename AssocMap<K, V>::iterator AssocMap<K, V>::erase(typename AssocMap<K, V>::const_iterator first, typename AssocMap<K, V>::const_iterator last)
		{
			data.erase(keys.at(first), keys.at(last));
			return keys.erase(first, last);
		}
		
		template<typename K, typename V>
		void AssocMap<K, V>::clear() noexcept
		{
			data.clear();
			keys.clear();
		}
	}
}

#endif // ASSOC_MAP_HPP
