






class Patient : public Table
{
    Q_OBJECT public: Patient& operator=(Queryset* q){ this->exec(q); return *this;} public: Q_PROPERTY(QString id READ id WRITE setid) Q_CLASSINFO("id", "integer PRIMARYKEY AUTO_INCREMENT") QString id() const{ return m_id;} void setid(const QString &id){ m_id = id;} private: QString m_id; public: Q_PROPERTY(QString updated_at READ updated_at WRITE setupdated_at) Q_CLASSINFO("updated_at", "timestamp NOT_NULL") QString updated_at() const{ return m_updated_at;} void setupdated_at(const QString &updated_at){ m_updated_at = updated_at;} private: QString m_updated_at; public: Q_PROPERTY(QString created_at READ created_at WRITE setcreated_at) Q_CLASSINFO("created_at", "timestamp NOT NULL") QString created_at() const{ return m_created_at;} void setcreated_at(const QString &created_at){ m_created_at = created_at;} private: QString m_created_at;
    public: Q_PROPERTY(QString name READ name WRITE setname) Q_CLASSINFO("name", "varchar(255)") QString name() const{ return m_name;} void setname(const QString &name){ m_name = name;} private: QString m_name;



};
