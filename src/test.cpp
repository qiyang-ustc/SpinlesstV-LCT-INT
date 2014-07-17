#include <alps/ngs.hpp>
#include <alps/parseargs.hpp>
#include "interaction_expansion.hpp"

void InteractionExpansion::test(){
    
      for (unsigned iblock = 0; iblock < 1; ++iblock ){// sweep through blocks 

                //we jump to a new block and calculate gf at its time origin
                gf.wrap(iblock*blocksize, tlist, vlist); //this is necessary because otherwise we might jump over it_ some empty block 

                std::vector<site_type> sites;  
            
                alps::graph_helper<>::bond_descriptor bond = lattice.bond(randomint(n_bond));
                sites.push_back(lattice.source(bond));
                sites.push_back(lattice.target(bond));
            
                itime_type itau = iblock*blocksize + randomint(blocksize);// a random time inside this block 
            
                std::cout << "######add#################"  << std::endl; 
                //std::cout << "weight before: " << 1./gf.G(0, tlist, vlist).determinant() << std::endl; 
                std::cout << "itau, iblock:"  << itau << " " << iblock << std::endl; 

                double detratio = add_impl(itau, sites, false);  

                //std::cout << "weight after: " << 1./gf.G(0, tlist, vlist).determinant() << std::endl; 
                //std::cout << "tlist: "; 
                //std::copy(tlist.begin(), tlist.end(), std::ostream_iterator<itime_type>(std::cout, " "));
                //std::cout << std::endl; 
                std::cout << "add vertex with detratio: " << std::setprecision(9)  << detratio<< std::endl; 
                std::cout << "number of vertices: " << tlist.size() << std::endl; 
                gf.rebuild(tlist, vlist);
      }
        /*
      {
            
                if (tlist.size()< 1) continue; 

                tlist_type::const_iterator lower, upper; 
                lower = std::lower_bound (tlist.begin(), tlist.end(), iblock*blocksize); 
                upper = std::upper_bound (tlist.begin(), tlist.end(), (iblock+1)*blocksize, std::less_equal<itime_type>());  //equal is exclude
   
                unsigned num_vertices = std::distance(lower, upper); //number of vertices in this block
   
                if(num_vertices < 1){
                    return; 
                }
                
                std::advance(lower, randomint(num_vertices)); //the vertex to remove 
                itime_type itau = *lower; 

                std::cout << "####remove###################"  << std::endl; 
                std::cout << "itau, block:"  << itau << " " << b << std::endl; 
                //std::cout << "weight before: " << 1./gf.G(0, tlist, vlist).determinant() << std::endl; 

                double detratio = remove_impl(itau, false); 
                
                //std::cout << "weight after: " << 1./gf.G(0, tlist, vlist).determinant() << std::endl; 
                std::cout << "tlist: "; 
                std::copy(tlist.begin(), tlist.end(), std::ostream_iterator<itime_type>(std::cout, " "));
                std::cout << std::endl; 
                std::cout << "itry, remove vertex with detratio: " << itry << " "<<  std::setprecision(9)  << detratio<< std::endl; 
                std::cout << "number of vertices: " << tlist.size() << std::endl; 
        }
        */
            
}


int main(int argc, char** argv){
   alps::parseargs options(argc, argv); 
   alps::params params(options.input_file);

   InteractionExpansion sim(params, 0); 
   std::cout << "initialization done" << std::endl; 
   sim.test(); 
   return 0; 
}

