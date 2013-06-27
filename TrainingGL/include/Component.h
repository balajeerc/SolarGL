namespace SolarGL
{
    class Component
    {
    public:
        /// \brief  Constructor
        Component();

        /// \brief  Gets a component of this node by name
        /// \detail Returns NULL if a component by the name could not be found
        Component* getComponentByName(const std::string& component) const;

        /// \brief  Gets a component of this node by name
        void addComponent(const std::string& name, const Component& component);
    };
}