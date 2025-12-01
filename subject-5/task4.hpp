#include <iostream>
#include <memory>
#include <string>

class API {
public:
    API();
    
    // Destructor MUST be declared here, but defined in the .cpp 
    // where Impl is defined.
    ~API(); 

    // Move operations are required because unique_ptr is not copyable.
    // We declare them here, but we must define them in the .cpp file
    // because unique_ptr needs the complete type of Impl to verify deletion.
    API(API&&) noexcept;
    API& operator=(API&&) noexcept;

    void execute();

private:
    // Forward declaration of the implementation struct (Incomplete type)
    struct Impl;
    
    // Opaque pointer. 
    // std::unique_ptr checks sizeof(Impl) > 0 at the point of deletion.
    std::unique_ptr<Impl> pImpl; 
};
