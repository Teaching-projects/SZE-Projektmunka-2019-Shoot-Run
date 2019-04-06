// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "event-odb.hxx"
#include "image-odb.hxx"
#include "tardis-odb.hxx"
#include "track-odb.hxx"
#include "user-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy


#include <odb/mysql/traits.hxx>
#include <odb/mysql/database.hxx>
#include <odb/mysql/transaction.hxx>
#include <odb/mysql/connection.hxx>
#include <odb/mysql/statement.hxx>
#include <odb/mysql/statement-cache.hxx>
#include <odb/mysql/simple-object-statements.hxx>
#include <odb/mysql/container-statements.hxx>
#include <odb/mysql/exceptions.hxx>
#include <odb/mysql/simple-object-result.hxx>
#include <odb/mysql/enum.hxx>

namespace odb
{
  // event
  //

  const char alias_traits<  ::user,
    id_mysql,
    access::object_traits_impl< ::event, id_mysql >::submitter_id_tag>::
  table_name[] = "`submitter_id`";

  struct access::object_traits_impl< ::event, id_mysql >::extra_statement_cache_type
  {
    mysql::container_statements_impl< tracks_traits > tracks_;
    mysql::container_statements_impl< images_traits > images_;

    extra_statement_cache_type (
      mysql::connection& c,
      image_type&,
      id_image_type&,
      mysql::binding& id,
      mysql::binding&)
    : tracks_ (c, id),
      images_ (c, id)
    {
    }
  };

  // tracks_
  //

  const char access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  select_statement[] =
  "SELECT "
  "`track`.`track_id` "
  "FROM `track` "
  "WHERE `track`.`track_id`=?";

  const char access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  insert_statement[] =
  "";

  const char access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  delete_statement[] =
  "";

  void access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  bind (MYSQL_BIND* b,
        const MYSQL_BIND* id,
        std::size_t id_size,
        data_image_type& d)
  {
    using namespace mysql;

    statement_kind sk (statement_select);
    ODB_POTENTIALLY_UNUSED (sk);

    size_t n (0);

    // object_id
    //
    if (id != 0)
      std::memcpy (&b[n], id, id_size * sizeof (id[0]));
    n += id_size;

    // value
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &d.value_value;
    b[n].is_null = &d.value_null;
  }

  void access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  grow (data_image_type& i,
        my_bool* t)
  {
    bool grew (false);

    // value
    //
    t[0UL] = 0;

    if (grew)
      i.version++;
  }

  void access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  init (value_type& v,
        const data_image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (db);

    // value
    //
    {
      typedef object_traits< ::track > obj_traits;
      typedef odb::pointer_traits< value_type > ptr_traits;

      if (i.value_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_value (
          id,
          i.value_value,
          i.value_null);

        v = ptr_traits::pointer_type (
          *static_cast<mysql::database*> (db), id);
      }
    }
  }

  void access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  insert (index_type, const value_type&, void*)
  {
  }

  bool access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  select (index_type&, value_type& v, void* d)
  {
    using namespace mysql;
    using mysql::select_statement;

    statements_type& sts (*static_cast< statements_type* > (d));
    data_image_type& di (sts.data_image ());

    init (v, di, &sts.connection ().database ());

    select_statement& st (sts.select_statement ());
    select_statement::result r (st.fetch ());
    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  delete_ (void*)
  {
  }

  void access::object_traits_impl< ::event, id_mysql >::tracks_traits::
  load (container_type& c,
        statements_type& sts)
  {
    using namespace mysql;
    using mysql::select_statement;

    const binding& id (sts.id_binding ());

    if (sts.data_binding_test_version ())
    {
      bind (sts.data_bind (), id.bind, id.count, sts.data_image ());
      sts.data_binding_update_version ();
    }

    select_statement& st (sts.select_statement ());
    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());
    bool more (r != select_statement::no_data);

    functions_type& fs (sts.functions ());
    fs.ordered_ = false;
    container_traits_type::load (c, more, fs);
  }

  // images_
  //

  const char access::object_traits_impl< ::event, id_mysql >::images_traits::
  select_statement[] =
  "SELECT "
  "`image`.`image_id` "
  "FROM `image` "
  "WHERE `image`.`image_id`=?";

  const char access::object_traits_impl< ::event, id_mysql >::images_traits::
  insert_statement[] =
  "";

  const char access::object_traits_impl< ::event, id_mysql >::images_traits::
  delete_statement[] =
  "";

  void access::object_traits_impl< ::event, id_mysql >::images_traits::
  bind (MYSQL_BIND* b,
        const MYSQL_BIND* id,
        std::size_t id_size,
        data_image_type& d)
  {
    using namespace mysql;

    statement_kind sk (statement_select);
    ODB_POTENTIALLY_UNUSED (sk);

    size_t n (0);

    // object_id
    //
    if (id != 0)
      std::memcpy (&b[n], id, id_size * sizeof (id[0]));
    n += id_size;

    // value
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &d.value_value;
    b[n].is_null = &d.value_null;
  }

  void access::object_traits_impl< ::event, id_mysql >::images_traits::
  grow (data_image_type& i,
        my_bool* t)
  {
    bool grew (false);

    // value
    //
    t[0UL] = 0;

    if (grew)
      i.version++;
  }

  void access::object_traits_impl< ::event, id_mysql >::images_traits::
  init (value_type& v,
        const data_image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (db);

    // value
    //
    {
      typedef object_traits< ::image > obj_traits;
      typedef odb::pointer_traits< value_type > ptr_traits;

      if (i.value_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_value (
          id,
          i.value_value,
          i.value_null);

        v = ptr_traits::pointer_type (
          *static_cast<mysql::database*> (db), id);
      }
    }
  }

  void access::object_traits_impl< ::event, id_mysql >::images_traits::
  insert (index_type, const value_type&, void*)
  {
  }

  bool access::object_traits_impl< ::event, id_mysql >::images_traits::
  select (index_type&, value_type& v, void* d)
  {
    using namespace mysql;
    using mysql::select_statement;

    statements_type& sts (*static_cast< statements_type* > (d));
    data_image_type& di (sts.data_image ());

    init (v, di, &sts.connection ().database ());

    select_statement& st (sts.select_statement ());
    select_statement::result r (st.fetch ());
    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::event, id_mysql >::images_traits::
  delete_ (void*)
  {
  }

  void access::object_traits_impl< ::event, id_mysql >::images_traits::
  load (container_type& c,
        statements_type& sts)
  {
    using namespace mysql;
    using mysql::select_statement;

    const binding& id (sts.id_binding ());

    if (sts.data_binding_test_version ())
    {
      bind (sts.data_bind (), id.bind, id.count, sts.data_image ());
      sts.data_binding_update_version ();
    }

    select_statement& st (sts.select_statement ());
    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());
    bool more (r != select_statement::no_data);

    functions_type& fs (sts.functions ());
    fs.ordered_ = false;
    container_traits_type::load (c, more, fs);
  }

  access::object_traits_impl< ::event, id_mysql >::id_type
  access::object_traits_impl< ::event, id_mysql >::
  id (const id_image_type& i)
  {
    mysql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_value (
        id,
        i.id_value,
        i.id_null);
    }

    return id;
  }

  access::object_traits_impl< ::event, id_mysql >::id_type
  access::object_traits_impl< ::event, id_mysql >::
  id (const image_type& i)
  {
    mysql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_value (
        id,
        i.event_id_value,
        i.event_id_null);
    }

    return id;
  }

  bool access::object_traits_impl< ::event, id_mysql >::
  grow (image_type& i,
        my_bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // event_id
    //
    t[0UL] = 0;

    // event_name
    //
    if (t[1UL])
    {
      i.event_name_value.capacity (i.event_name_size);
      grew = true;
    }

    // submit_date
    //
    t[2UL] = 0;

    // event_accepted
    //
    t[3UL] = 0;

    // submitter_id
    //
    t[4UL] = 0;

    return grew;
  }

  void access::object_traits_impl< ::event, id_mysql >::
  bind (MYSQL_BIND* b,
        image_type& i,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    std::size_t n (0);

    // event_id
    //
    if (sk != statement_update)
    {
      b[n].buffer_type = MYSQL_TYPE_LONG;
      b[n].is_unsigned = 1;
      b[n].buffer = &i.event_id_value;
      b[n].is_null = &i.event_id_null;
      n++;
    }

    // event_name
    //
    b[n].buffer_type = MYSQL_TYPE_STRING;
    b[n].buffer = i.event_name_value.data ();
    b[n].buffer_length = static_cast<unsigned long> (
      i.event_name_value.capacity ());
    b[n].length = &i.event_name_size;
    b[n].is_null = &i.event_name_null;
    n++;

    // submit_date
    //
    b[n].buffer_type = MYSQL_TYPE_DATETIME;
    b[n].buffer = &i.submit_date_value;
    b[n].is_null = &i.submit_date_null;
    n++;

    // event_accepted
    //
    b[n].buffer_type = MYSQL_TYPE_TINY;
    b[n].is_unsigned = 0;
    b[n].buffer = &i.event_accepted_value;
    b[n].is_null = &i.event_accepted_null;
    n++;

    // submitter_id
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i.submitter_id_value;
    b[n].is_null = &i.submitter_id_null;
    n++;
  }

  void access::object_traits_impl< ::event, id_mysql >::
  bind (MYSQL_BIND* b, id_image_type& i)
  {
    std::size_t n (0);
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i.id_value;
    b[n].is_null = &i.id_null;
  }

  bool access::object_traits_impl< ::event, id_mysql >::
  init (image_type& i,
        const object_type& o,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    bool grew (false);

    // event_id
    //
    if (sk == statement_insert)
    {
      unsigned int const& v =
        o.event_id;

      bool is_null (false);
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_image (
        i.event_id_value, is_null, v);
      i.event_id_null = is_null;
    }

    // event_name
    //
    {
      ::std::string const& v =
        o.event_name;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.event_name_value.capacity ());
      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_image (
        i.event_name_value,
        size,
        is_null,
        v);
      i.event_name_null = is_null;
      i.event_name_size = static_cast<unsigned long> (size);
      grew = grew || (cap != i.event_name_value.capacity ());
    }

    // submit_date
    //
    {
      ::QDateTime const& v =
        o.submit_date;

      bool is_null (true);
      mysql::value_traits<
          ::QDateTime,
          mysql::id_datetime >::set_image (
        i.submit_date_value, is_null, v);
      i.submit_date_null = is_null;
    }

    // event_accepted
    //
    {
      bool const& v =
        o.event_accepted;

      bool is_null (false);
      mysql::value_traits<
          bool,
          mysql::id_tiny >::set_image (
        i.event_accepted_value, is_null, v);
      i.event_accepted_null = is_null;
    }

    // submitter_id
    //
    {
      ::QLazySharedPointer< ::user > const& v =
        o.submitter_id;

      typedef object_traits< ::user > obj_traits;
      typedef odb::pointer_traits< ::QLazySharedPointer< ::user > > ptr_traits;

      bool is_null (ptr_traits::null_ptr (v));
      if (!is_null)
      {
        const obj_traits::id_type& id (
          ptr_traits::object_id< ptr_traits::element_type  > (v));

        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_image (
          i.submitter_id_value, is_null, id);
        i.submitter_id_null = is_null;
      }
      else
        throw null_pointer ();
    }

    return grew;
  }

  void access::object_traits_impl< ::event, id_mysql >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // event_id
    //
    {
      unsigned int& v =
        o.event_id;

      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_value (
        v,
        i.event_id_value,
        i.event_id_null);
    }

    // event_name
    //
    {
      ::std::string& v =
        o.event_name;

      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_value (
        v,
        i.event_name_value,
        i.event_name_size,
        i.event_name_null);
    }

    // submit_date
    //
    {
      ::QDateTime& v =
        o.submit_date;

      mysql::value_traits<
          ::QDateTime,
          mysql::id_datetime >::set_value (
        v,
        i.submit_date_value,
        i.submit_date_null);
    }

    // event_accepted
    //
    {
      bool& v =
        o.event_accepted;

      mysql::value_traits<
          bool,
          mysql::id_tiny >::set_value (
        v,
        i.event_accepted_value,
        i.event_accepted_null);
    }

    // submitter_id
    //
    {
      ::QLazySharedPointer< ::user >& v =
        o.submitter_id;

      typedef object_traits< ::user > obj_traits;
      typedef odb::pointer_traits< ::QLazySharedPointer< ::user > > ptr_traits;

      if (i.submitter_id_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_value (
          id,
          i.submitter_id_value,
          i.submitter_id_null);

        v = ptr_traits::pointer_type (
          *static_cast<mysql::database*> (db), id);
      }
    }
  }

  void access::object_traits_impl< ::event, id_mysql >::
  init (id_image_type& i, const id_type& id)
  {
    {
      bool is_null (false);
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_image (
        i.id_value, is_null, id);
      i.id_null = is_null;
    }
  }

  const char access::object_traits_impl< ::event, id_mysql >::persist_statement[] =
  "INSERT INTO `event` "
  "(`event_id`, "
  "`event_name`, "
  "`submit_date`, "
  "`event_accepted`, "
  "`submitter_id`) "
  "VALUES "
  "(?, ?, ?, ?, ?)";

  const char access::object_traits_impl< ::event, id_mysql >::find_statement[] =
  "SELECT "
  "`event`.`event_id`, "
  "`event`.`event_name`, "
  "`event`.`submit_date`, "
  "`event`.`event_accepted`, "
  "`event`.`submitter_id` "
  "FROM `event` "
  "WHERE `event`.`event_id`=?";

  const char access::object_traits_impl< ::event, id_mysql >::update_statement[] =
  "UPDATE `event` "
  "SET "
  "`event_name`=?, "
  "`submit_date`=?, "
  "`event_accepted`=?, "
  "`submitter_id`=? "
  "WHERE `event_id`=?";

  const char access::object_traits_impl< ::event, id_mysql >::erase_statement[] =
  "DELETE FROM `event` "
  "WHERE `event_id`=?";

  const char access::object_traits_impl< ::event, id_mysql >::query_statement[] =
  "SELECT\n"
  "`event`.`event_id`,\n"
  "`event`.`event_name`,\n"
  "`event`.`submit_date`,\n"
  "`event`.`event_accepted`,\n"
  "`event`.`submitter_id`\n"
  "FROM `event`\n"
  "LEFT JOIN `user` AS `submitter_id` ON `submitter_id`.`user_id`=`event`.`submitter_id`";

  const char access::object_traits_impl< ::event, id_mysql >::erase_query_statement[] =
  "DELETE FROM `event`";

  const char access::object_traits_impl< ::event, id_mysql >::table_name[] =
  "`event`";

  void access::object_traits_impl< ::event, id_mysql >::
  persist (database& db, object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    im.event_id_value = 0;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    {
      id_image_type& i (sts.id_image ());
      binding& b (sts.id_image_binding ());
      if (i.version != sts.id_image_version () || b.version == 0)
      {
        bind (b.bind, i);
        sts.id_image_version (i.version);
        b.version++;
      }
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    obj.event_id = id (sts.id_image ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::event, id_mysql >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace mysql;
    using mysql::update_statement;

    callback (db, obj, callback_event::pre_update);

    mysql::transaction& tr (mysql::transaction::current ());
    mysql::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    const id_type& id (
      obj.event_id);
    id_image_type& idi (sts.id_image ());
    init (idi, id);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (idi.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (idi.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, idi);
        sts.id_image_version (idi.version);
        idb.version++;
      }

      sts.update_id_image_version (idi.version);

      if (!u)
        imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::event, id_mysql >::
  erase (database& db, const id_type& id)
  {
    using namespace mysql;

    ODB_POTENTIALLY_UNUSED (db);

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  access::object_traits_impl< ::event, id_mysql >::pointer_type
  access::object_traits_impl< ::event, id_mysql >::
  find (database& db, const id_type& id)
  {
    using namespace mysql;

    {
      pointer_type p (pointer_cache_traits::find (db, id));

      if (!pointer_traits::null_ptr (p))
        return p;
    }

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory<object_type, pointer_type>::create ());
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, p));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement ());
      ODB_POTENTIALLY_UNUSED (st);

      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);
      sts.load_delayed (0);
      l.unlock ();
      callback (db, obj, callback_event::post_load);
      pointer_cache_traits::load (ig.position ());
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::event, id_mysql >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::event, id_mysql >::
  reload (database& db, object_type& obj)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    const id_type& id  (
      obj.event_id);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::event, id_mysql >::
  find_ (statements_type& sts,
         const id_type* id)
  {
    using namespace mysql;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::event, id_mysql >::
  load_ (statements_type& sts,
         object_type& obj,
         bool reload)
  {
    ODB_POTENTIALLY_UNUSED (reload);

    extra_statement_cache_type& esc (sts.extra_statement_cache ());

    // tracks_
    //
    {
      ::std::vector< ::QLazyWeakPointer< ::track > >& v =
        obj.tracks_;

      tracks_traits::load (
        v,
        esc.tracks_);
    }

    // images_
    //
    {
      ::std::vector< ::QLazyWeakPointer< ::image > >& v =
        obj.images_;

      images_traits::load (
        v,
        esc.images_);
    }
  }

  result< access::object_traits_impl< ::event, id_mysql >::object_type >
  access::object_traits_impl< ::event, id_mysql >::
  query (database&, const query_base_type& q)
  {
    using namespace mysql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += "\n";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        text,
        true,
        true,
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) mysql::object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::event, id_mysql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      text,
      q.parameters_binding ());

    return st.execute ();
  }
}

#include <odb/post.hxx>
