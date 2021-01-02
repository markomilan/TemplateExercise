#ifndef MAPALIGN
#define MAPALIGN

#include <map>
#include <vector>
#include <typeinfo>
 
template<class K,class V,class S = std::less<K> >

class map_aligner
{
	private:
	
	std::vector<std::map<K,V,S>*> maps;
	std::vector<K> keys;
	typename std::map<K,V,S>::iterator itrM;
	typename std::vector<K>::iterator itrK;
	V filler;
	bool isFillerd;
	
	//osszes kulcs kigyujtese
	
	void getKeys()
	{		
		for(unsigned int i=0;i<maps.size();i++)
		{
			for(itrM = (*maps.at(i)).begin(); itrM != (*maps.at(i)).end(); itrM++)
			{
				bool contain = false;
				for(itrK = keys.begin(); itrK != keys.end(); ++itrK)
				{
					if(itrM->first == (*itrK))
					{
						contain = true;
					}
				}
				if(contain == false)
				{
					keys.push_back(itrM->first);
				}
			}
        }
	}
	
	public:
	
	map_aligner<K,V,S> &operator+=(std::map<K,V,S> &m){
        add(m);
        return *this;
    }
	
	void add(std::map<K,V,S>& m )
	{
		maps.push_back(&m);
	}
	
	const int count()
	{
        return maps.size();
    }
	
	void erase(K key)
	{
        for(unsigned int i=0;i<maps.size();i++)
		{
            (*maps.at(i)).erase(key);
        }
    }
	
	void set_filler(V filler)
	{
		(*this).filler = filler;
		isFillerd = true;
	}
	
	void align()
	{
		getKeys();
		
		//kulcsok behelyettesitve
		
		for(unsigned int i=0;i<maps.size();++i)
		{
			for(itrK = keys.begin(); itrK != keys.end(); ++itrK)
			{
				bool contain = false;
				
				for(itrM = (*maps.at(i)).begin(); itrM != (*maps.at(i)).end(); itrM++)
				{
					if(itrM->first == (*itrK))
					{
						contain = true;
					}
				}
				if(contain == false)
				{
					if (!isFillerd)
					{
						if (typeid(V) == typeid(int))
						{
							(*maps.at(i)).insert(std::pair<K,V>((*itrK),0));
						}
						else
						{
							(*maps.at(i)).insert(std::pair<K,V>((*itrK),filler));
						}
						
					}
					else
					{
						(*maps.at(i)).insert(std::pair<K,V>((*itrK),filler));
					}
				}
			}
			
			//eredmeny kiirasa
			
			/*for(typename std::map<K,V,S>::iterator it = (*maps.at(i)).begin() ; it!=(*maps.at(i)).end();++it)
			{
				std::cout<<it->first<<" "<<it->second<<",";
			}
			std::cout<<"\n";*/
			
		}
		//std::cout<<"\n";
		isFillerd = false;
	}
};


#endif