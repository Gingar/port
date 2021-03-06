/******************************************************************************
Este arquivo eh parte da implementacao do ambiente declarativo do middleware
Ginga (Ginga-NCL).

Direitos Autorais Reservados (c) 1989-2007 PUC-Rio/Laboratorio TeleMidia

Este programa eh software livre; voce pode redistribui-lo e/ou modificah-lo sob
os termos da Licenca Publica Geral GNU versao 2 conforme publicada pela Free
Software Foundation.

Este programa eh distribuido na expectativa de que seja util, porem, SEM
NENHUMA GARANTIA; nem mesmo a garantia implicita de COMERCIABILIDADE OU
ADEQUACAO A UMA FINALIDADE ESPECIFICA. Consulte a Licenca Publica Geral do
GNU versao 2 para mais detalhes.

Voce deve ter recebido uma copia da Licenca Publica Geral do GNU versao 2 junto
com este programa; se nao, escreva para a Free Software Foundation, Inc., no
endereco 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA.

Para maiores informacoes:
ncl @ telemidia.puc-rio.br
http://www.ncl.org.br
http://www.ginga.org.br
http://www.telemidia.puc-rio.br
******************************************************************************
This file is part of the declarative environment of middleware Ginga (Ginga-NCL)

Copyright: 1989-2007 PUC-RIO/LABORATORIO TELEMIDIA, All Rights Reserved.
  Copyright 2010 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata


This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License version 2 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License version 2 for more
details.

You should have received a copy of the GNU General Public License version 2
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA

For further information contact:
ncl @ telemidia.puc-rio.br
http://www.ncl.org.br
http://www.ginga.org.br
http://www.telemidia.puc-rio.br
*******************************************************************************/

#ifndef _FORMATTERSCHEDULER_H_
#define _FORMATTERSCHEDULER_H_

#include <system/util/mutex/dfbsurfacemutex.h>

#include <boost/thread/mutex.hpp>

#include "model/ExecutionObject.h"
#include "model/NodeNesting.h"
#include "model/CompositeExecutionObject.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::components;

#include "model/ExecutionObjectSwitch.h"
#include "model/SwitchEvent.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::switches;

#include "model/AttributionEvent.h"
#include "model/IEventListener.h"
#include "model/FormatterEvent.h"
#include "model/PresentationEvent.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::event;

#include "model/LinkAssignmentAction.h"
#include "model/LinkActionListener.h"
#include "model/LinkSimpleAction.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::link;

#include "model/FormatterLayout.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::presentation;

#include "adaptation/context/RuleAdapter.h"
#include "adaptation/context/PresentationContext.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::adaptation::context;

#include "adapters/application/ApplicationPlayerAdapter.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::adapters::application;

#include "adapters/FormatterPlayerAdapter.h"
#include "adapters/PlayerAdapterManager.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::adapters;

#include "ncl/connectors/SimpleAction.h"
#include "ncl/connectors/EventUtil.h"
using namespace ::br::pucrio::telemidia::ncl::connectors;

#include "ncl/components/CompositeNode.h"
#include "ncl/components/ContentNode.h"
#include "ncl/components/Node.h"
#include "ncl/components/NodeEntity.h"
using namespace ::br::pucrio::telemidia::ncl::components;

#include "ncl/interfaces/Port.h"
#include "ncl/interfaces/Anchor.h"
#include "ncl/interfaces/ContentAnchor.h"
#include "ncl/interfaces/PropertyAnchor.h"
#include "ncl/interfaces/SwitchPort.h"
using namespace ::br::pucrio::telemidia::ncl::interfaces;

#include "ncl/reuse/ReferNode.h"
using namespace ::br::pucrio::telemidia::ncl::reuse;

#include "focus/FormatterFocusManager.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::focus;

#include "multidevice/IFormatterMultiDevice.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::multidevice;

#include "IFormatterSchedulerListener.h"
#include "emconverter/ObjectCreationForbiddenException.h"

#include "animation/AnimationController.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::animation;

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

namespace br {
namespace pucrio {
namespace telemidia {
namespace ginga {
namespace ncl {
	class FormatterScheduler : public LinkActionListener,
		    public IEventListener {

		private:
			RuleAdapter* ruleAdapter;
			PlayerAdapterManager* playerManager;
			IFormatterMultiDevice* layoutManager;
			FormatterFocusManager* focusManager;

			void* compiler; //FormatterConverter*
			vector<IFormatterSchedulerListener*>* schedulerListeners;
			vector<FormatterEvent*>* documentEvents;
			map<FormatterEvent*, bool>* documentStatus;
			set<string> typeSet;
			::util::Singleton<DFBSurfaceMutex> _DFBSurfaceMutexSingleton;

			boost::mutex _eventMutex;
		public:
			FormatterScheduler(
				    PlayerAdapterManager* playerManager,
				    RuleAdapter* ruleAdapter,
				    IFormatterMultiDevice* multiDevice,
				    void* compiler); //FormatterConverter

			virtual ~FormatterScheduler();

			void stopListening(void* event);
			bool setKeyHandler(bool isHandler);
			void setStandByState(bool standBy);
			FormatterFocusManager* getFocusManager();
			FormatterLayout* getFormatterLayout(
					CascadingDescriptor* descriptor);

		private:
			bool isDocumentRunning(FormatterEvent* event);

			void setTimeBaseObject(
				    ExecutionObject* object,
				    FormatterPlayerAdapter* objectPlayer, string nodeId);

		public:
			void runAction(void* action);

		private:
			void runAction(FormatterEvent* event, void* action);
			void runActionOverProperty(
					FormatterEvent* event,
					LinkSimpleAction* action);

			void runActionOverApplicationObject(
					ApplicationExecutionObject* executionObject,
					FormatterEvent* event,
					FormatterPlayerAdapter* player,
					LinkSimpleAction* action);

			void runActionOverComposition(
				    CompositeExecutionObject* compositeObject,
				    LinkSimpleAction* action);

			void runActionOverSwitch(
				    ExecutionObjectSwitch* switchObject,
				    SwitchEvent* event,
				    LinkSimpleAction* action);

			void runSwitchEvent(
				    ExecutionObjectSwitch* switchObject,
				    SwitchEvent* switchEvent,
				    ExecutionObject* selectedObject,
				    LinkSimpleAction* action);

			string solveImplicitRefAssessment(
					string propValue,
					LinkAssignmentAction* action, AttributionEvent* event);

		public:
			void startEvent(FormatterEvent* event);
			void stopEvent(FormatterEvent* event);
			void pauseEvent(FormatterEvent* event);
			void resumeEvent(FormatterEvent* event);

		private:
			void initializeDefaultSettings();
			void initializeDocumentSettings(Node* node);

		public:
			void startDocument(
				    FormatterEvent* documentEvent,
				    vector<FormatterEvent*>* entryEvents);

		private:
			void removeDocument(FormatterEvent* documentEvent);

		public:
			void stopDocument(FormatterEvent* documentEvent);
			void pauseDocument(FormatterEvent* documentEvent);
			void resumeDocument(FormatterEvent* documentEvent);
			void stopAllDocuments();
			void pauseAllDocuments();
			void resumeAllDocuments();
			void eventStateChanged(
				    void* someEvent, short transition, short previousState);

			short getPriorityType();
			void addSchedulerListener(IFormatterSchedulerListener* listener);
			void removeSchedulerListener(IFormatterSchedulerListener* listener);
	};
}
}
}
}
}

#endif //_FORMATTERSCHEDULER_H_
