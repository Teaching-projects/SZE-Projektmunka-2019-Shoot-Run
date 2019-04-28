// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "image-odb.hxx"
#include "event-odb.hxx"
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
  // image
  //

  const char alias_traits<  ::odbevent,
    id_mysql,
    access::object_traits_impl< ::image, id_mysql >::event_id_tag>::
  table_name[] = "`event_id`";

  const char alias_traits<  ::user,
    id_mysql,
    access::object_traits_impl< ::image, id_mysql >::user_id_tag>::
  table_name[] = "`user_id`";

  struct access::object_traits_impl< ::image, id_mysql >::extra_statement_cache_type
  {
    extra_statement_cache_type (
      mysql::connection&,
      image_type&,
      id_image_type&,
      mysql::binding&,
      mysql::binding&)
    {
    }
  };

  access::object_traits_impl< ::image, id_mysql >::id_type
  access::object_traits_impl< ::image, id_mysql >::
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

  access::object_traits_impl< ::image, id_mysql >::id_type
  access::object_traits_impl< ::image, id_mysql >::
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
        i.image_id_value,
        i.image_id_null);
    }

    return id;
  }

  bool access::object_traits_impl< ::image, id_mysql >::
  grow (image_type& i,
        my_bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // image_id
    //
    t[0UL] = 0;

    // PATH
    //
    if (t[1UL])
    {
      i.PATH_value.capacity (i.PATH_size);
      grew = true;
    }

    // event_id
    //
    t[2UL] = 0;

    // user_id
    //
    t[3UL] = 0;

    // image_date
    //
    t[4UL] = 0;

    // image_accepted
    //
    t[5UL] = 0;

    // image_longitude
    //
    t[6UL] = 0;

    // image_latitude
    //
    t[7UL] = 0;

    // blob
    //
    if (t[8UL])
    {
      i.blob_value.capacity (i.blob_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::image, id_mysql >::
  bind (MYSQL_BIND* b,
        image_type& i,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    std::size_t n (0);

    // image_id
    //
    if (sk != statement_update)
    {
      b[n].buffer_type = MYSQL_TYPE_LONG;
      b[n].is_unsigned = 1;
      b[n].buffer = &i.image_id_value;
      b[n].is_null = &i.image_id_null;
      n++;
    }

    // PATH
    //
    b[n].buffer_type = MYSQL_TYPE_STRING;
    b[n].buffer = i.PATH_value.data ();
    b[n].buffer_length = static_cast<unsigned long> (
      i.PATH_value.capacity ());
    b[n].length = &i.PATH_size;
    b[n].is_null = &i.PATH_null;
    n++;

    // event_id
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i.event_id_value;
    b[n].is_null = &i.event_id_null;
    n++;

    // user_id
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i.user_id_value;
    b[n].is_null = &i.user_id_null;
    n++;

    // image_date
    //
    b[n].buffer_type = MYSQL_TYPE_DATETIME;
    b[n].buffer = &i.image_date_value;
    b[n].is_null = &i.image_date_null;
    n++;

    // image_accepted
    //
    b[n].buffer_type = MYSQL_TYPE_TINY;
    b[n].is_unsigned = 0;
    b[n].buffer = &i.image_accepted_value;
    b[n].is_null = &i.image_accepted_null;
    n++;

    // image_longitude
    //
    b[n].buffer_type = MYSQL_TYPE_DOUBLE;
    b[n].buffer = &i.image_longitude_value;
    b[n].is_null = &i.image_longitude_null;
    n++;

    // image_latitude
    //
    b[n].buffer_type = MYSQL_TYPE_DOUBLE;
    b[n].buffer = &i.image_latitude_value;
    b[n].is_null = &i.image_latitude_null;
    n++;

    // blob
    //
    b[n].buffer_type = MYSQL_TYPE_BLOB;
    b[n].buffer = i.blob_value.data ();
    b[n].buffer_length = static_cast<unsigned long> (
      i.blob_value.capacity ());
    b[n].length = &i.blob_size;
    b[n].is_null = &i.blob_null;
    n++;
  }

  void access::object_traits_impl< ::image, id_mysql >::
  bind (MYSQL_BIND* b, id_image_type& i)
  {
    std::size_t n (0);
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i.id_value;
    b[n].is_null = &i.id_null;
  }

  bool access::object_traits_impl< ::image, id_mysql >::
  init (image_type& i,
        const object_type& o,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    bool grew (false);

    // image_id
    //
    if (sk == statement_insert)
    {
      unsigned int const& v =
        o.image_id;

      bool is_null (false);
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_image (
        i.image_id_value, is_null, v);
      i.image_id_null = is_null;
    }

    // PATH
    //
    {
      ::std::string const& v =
        o.PATH;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.PATH_value.capacity ());
      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_image (
        i.PATH_value,
        size,
        is_null,
        v);
      i.PATH_null = is_null;
      i.PATH_size = static_cast<unsigned long> (size);
      grew = grew || (cap != i.PATH_value.capacity ());
    }

    // event_id
    //
    {
      ::QLazySharedPointer< ::odbevent > const& v =
        o.event_id;

      typedef object_traits< ::odbevent > obj_traits;
      typedef odb::pointer_traits< ::QLazySharedPointer< ::odbevent > > ptr_traits;

      bool is_null (ptr_traits::null_ptr (v));
      if (!is_null)
      {
        const obj_traits::id_type& id (
          ptr_traits::object_id< ptr_traits::element_type  > (v));

        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_image (
          i.event_id_value, is_null, id);
        i.event_id_null = is_null;
      }
      else
        throw null_pointer ();
    }

    // user_id
    //
    {
      ::QLazySharedPointer< ::user > const& v =
        o.user_id;

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
          i.user_id_value, is_null, id);
        i.user_id_null = is_null;
      }
      else
        throw null_pointer ();
    }

    // image_date
    //
    {
      ::QDateTime const& v =
        o.image_date;

      bool is_null (true);
      mysql::value_traits<
          ::QDateTime,
          mysql::id_datetime >::set_image (
        i.image_date_value, is_null, v);
      i.image_date_null = is_null;
    }

    // image_accepted
    //
    {
      bool const& v =
        o.image_accepted;

      bool is_null (false);
      mysql::value_traits<
          bool,
          mysql::id_tiny >::set_image (
        i.image_accepted_value, is_null, v);
      i.image_accepted_null = is_null;
    }

    // image_longitude
    //
    {
      double const& v =
        o.image_longitude;

      bool is_null (false);
      mysql::value_traits<
          double,
          mysql::id_double >::set_image (
        i.image_longitude_value, is_null, v);
      i.image_longitude_null = is_null;
    }

    // image_latitude
    //
    {
      double const& v =
        o.image_latitude;

      bool is_null (false);
      mysql::value_traits<
          double,
          mysql::id_double >::set_image (
        i.image_latitude_value, is_null, v);
      i.image_latitude_null = is_null;
    }

    // blob
    //
    {
      ::QByteArray const& v =
        o.blob;

      bool is_null (true);
      std::size_t size (0);
      std::size_t cap (i.blob_value.capacity ());
      mysql::value_traits<
          ::QByteArray,
          mysql::id_blob >::set_image (
        i.blob_value,
        size,
        is_null,
        v);
      i.blob_null = is_null;
      i.blob_size = static_cast<unsigned long> (size);
      grew = grew || (cap != i.blob_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::image, id_mysql >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // image_id
    //
    {
      unsigned int& v =
        o.image_id;

      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_value (
        v,
        i.image_id_value,
        i.image_id_null);
    }

    // PATH
    //
    {
      ::std::string& v =
        o.PATH;

      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_value (
        v,
        i.PATH_value,
        i.PATH_size,
        i.PATH_null);
    }

    // event_id
    //
    {
      ::QLazySharedPointer< ::odbevent >& v =
        o.event_id;

      typedef object_traits< ::odbevent > obj_traits;
      typedef odb::pointer_traits< ::QLazySharedPointer< ::odbevent > > ptr_traits;

      if (i.event_id_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_value (
          id,
          i.event_id_value,
          i.event_id_null);

        v = ptr_traits::pointer_type (
          *static_cast<mysql::database*> (db), id);
      }
    }

    // user_id
    //
    {
      ::QLazySharedPointer< ::user >& v =
        o.user_id;

      typedef object_traits< ::user > obj_traits;
      typedef odb::pointer_traits< ::QLazySharedPointer< ::user > > ptr_traits;

      if (i.user_id_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_value (
          id,
          i.user_id_value,
          i.user_id_null);

        v = ptr_traits::pointer_type (
          *static_cast<mysql::database*> (db), id);
      }
    }

    // image_date
    //
    {
      ::QDateTime& v =
        o.image_date;

      mysql::value_traits<
          ::QDateTime,
          mysql::id_datetime >::set_value (
        v,
        i.image_date_value,
        i.image_date_null);
    }

    // image_accepted
    //
    {
      bool& v =
        o.image_accepted;

      mysql::value_traits<
          bool,
          mysql::id_tiny >::set_value (
        v,
        i.image_accepted_value,
        i.image_accepted_null);
    }

    // image_longitude
    //
    {
      double& v =
        o.image_longitude;

      mysql::value_traits<
          double,
          mysql::id_double >::set_value (
        v,
        i.image_longitude_value,
        i.image_longitude_null);
    }

    // image_latitude
    //
    {
      double& v =
        o.image_latitude;

      mysql::value_traits<
          double,
          mysql::id_double >::set_value (
        v,
        i.image_latitude_value,
        i.image_latitude_null);
    }

    // blob
    //
    {
      ::QByteArray& v =
        o.blob;

      mysql::value_traits<
          ::QByteArray,
          mysql::id_blob >::set_value (
        v,
        i.blob_value,
        i.blob_size,
        i.blob_null);
    }
  }

  void access::object_traits_impl< ::image, id_mysql >::
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

  const char access::object_traits_impl< ::image, id_mysql >::persist_statement[] =
  "INSERT INTO `image` "
  "(`image_id`, "
  "`PATH`, "
  "`event_id`, "
  "`user_id`, "
  "`image_date`, "
  "`image_accepted`, "
  "`image_longitude`, "
  "`image_latitude`, "
  "`blob`) "
  "VALUES "
  "(?, ?, ?, ?, ?, ?, ?, ?, ?)";

  const char access::object_traits_impl< ::image, id_mysql >::find_statement[] =
  "SELECT "
  "`image`.`image_id`, "
  "`image`.`PATH`, "
  "`image`.`event_id`, "
  "`image`.`user_id`, "
  "`image`.`image_date`, "
  "`image`.`image_accepted`, "
  "`image`.`image_longitude`, "
  "`image`.`image_latitude`, "
  "`image`.`blob` "
  "FROM `image` "
  "WHERE `image`.`image_id`=?";

  const char access::object_traits_impl< ::image, id_mysql >::update_statement[] =
  "UPDATE `image` "
  "SET "
  "`PATH`=?, "
  "`event_id`=?, "
  "`user_id`=?, "
  "`image_date`=?, "
  "`image_accepted`=?, "
  "`image_longitude`=?, "
  "`image_latitude`=?, "
  "`blob`=? "
  "WHERE `image_id`=?";

  const char access::object_traits_impl< ::image, id_mysql >::erase_statement[] =
  "DELETE FROM `image` "
  "WHERE `image_id`=?";

  const char access::object_traits_impl< ::image, id_mysql >::query_statement[] =
  "SELECT\n"
  "`image`.`image_id`,\n"
  "`image`.`PATH`,\n"
  "`image`.`event_id`,\n"
  "`image`.`user_id`,\n"
  "`image`.`image_date`,\n"
  "`image`.`image_accepted`,\n"
  "`image`.`image_longitude`,\n"
  "`image`.`image_latitude`,\n"
  "`image`.`blob`\n"
  "FROM `image`\n"
  "LEFT JOIN `odbevent` AS `event_id` ON `event_id`.`event_id`=`image`.`event_id`\n"
  "LEFT JOIN `user` AS `user_id` ON `user_id`.`user_id`=`image`.`user_id`";

  const char access::object_traits_impl< ::image, id_mysql >::erase_query_statement[] =
  "DELETE FROM `image`";

  const char access::object_traits_impl< ::image, id_mysql >::table_name[] =
  "`image`";

  void access::object_traits_impl< ::image, id_mysql >::
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

    im.image_id_value = 0;

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

    obj.image_id = id (sts.id_image ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::image, id_mysql >::
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
      obj.image_id);
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

  void access::object_traits_impl< ::image, id_mysql >::
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

  access::object_traits_impl< ::image, id_mysql >::pointer_type
  access::object_traits_impl< ::image, id_mysql >::
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

  bool access::object_traits_impl< ::image, id_mysql >::
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

  bool access::object_traits_impl< ::image, id_mysql >::
  reload (database& db, object_type& obj)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    const id_type& id  (
      obj.image_id);

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

  bool access::object_traits_impl< ::image, id_mysql >::
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

  result< access::object_traits_impl< ::image, id_mysql >::object_type >
  access::object_traits_impl< ::image, id_mysql >::
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

  unsigned long long access::object_traits_impl< ::image, id_mysql >::
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
