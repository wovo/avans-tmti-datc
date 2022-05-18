// wouter.vanooijen@cboost.nl

#include <vector>

class game_object;

class component {
    game_object *p;
public:    
    component( game_object *p ): p( p ){}
    virtual void draw() = 0;
};

class penguin : public component {
public:
    void draw() override { }
    penguin( game_object * gop ): 
        component( gop )
    { }
};

class game_object {
    std::vector< component* > components;
public:
    template< typename T >
    void add(){
        components.push_back( new T( this ) );
    }
    
    void add( component *p ){
        components.push_back( p );
    }
    
    void draw(){
        for( auto c : components ){
            c->draw( components );
        }
    }
};

int main(){
    game_object g;
    g.add< penguin >();
    g.add( new penguin( & g ) );
}
