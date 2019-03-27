/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef mitkRESTServerQt_h
#define mitkRESTServerQt_h

#include <QThread>
#include <mitkRESTServer.h>

namespace mitk
{
  class RESTServerQt : public QObject, public RESTServer
  {
    Q_OBJECT 


  public:
    /**
     * @brief Creates an server listening to the given URI
     *
     * @param uri the URI at which the server is listening for requests
     */
    RESTServerQt(const web::uri &uri);
    ~RESTServerQt();

  public slots:
    /**
     * @brief Opens the listener and starts the listening process
     */
    void OpenListener();

    /**
     * @brief Closes the listener and stops the listening process
     */
    void CloseListener();
  };
} // namespace mitk
#endif