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

#ifndef FORMATTERCONVERTER_H_
#define FORMATTERCONVERTER_H_

#include "ncl/switches/SwitchNode.h"
using namespace ::br::pucrio::telemidia::ncl::switches;

#include "ncl/interfaces/PropertyAnchor.h"
#include "ncl/interfaces/ContentAnchor.h"
#include "ncl/interfaces/LambdaAnchor.h"
#include "ncl/interfaces/SwitchPort.h"
#include "ncl/interfaces/Port.h"
#include "ncl/interfaces/InterfacePoint.h"
using namespace ::br::pucrio::telemidia::ncl::interfaces;

#include "ncl/components/CompositeNode.h"
#include "ncl/components/ContextNode.h"
#include "ncl/components/ContentNode.h"
#include "ncl/components/Node.h"
#include "ncl/components/NodeEntity.h"
using namespace ::br::pucrio::telemidia::ncl::components;

#include "ncl/connectors/EventUtil.h"
using namespace ::br::pucrio::telemidia::ncl::connectors;

#include "ncl/descriptor/GenericDescriptor.h"
using namespace ::br::pucrio::telemidia::ncl::descriptor;

#include "ncl/link/Bind.h"
#include "ncl/link/CausalLink.h"
#include "ncl/link/Link.h"
using namespace ::br::pucrio::telemidia::ncl::link;

#include "ncl/reuse/ReferNode.h"
using namespace ::br::pucrio::telemidia::ncl::reuse;

#include "../model/ExecutionObjectSwitch.h"
#include "../model/SwitchEvent.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::switches;

#include "../model/AttributionEvent.h"
#include "../model/PresentationEvent.h"
#include "../model/SelectionEvent.h"
#include "../model/IEventListener.h"
#include "../model/FormatterEvent.h"
#include "../model/PresentationEvent.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::event;

#include "../model/FormatterCausalLink.h"
#include "../model/FormatterLink.h"
#include "../model/LinkAction.h"
#include "../model/LinkCompoundAction.h"
#include "../model/LinkSimpleAction.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::link;

#include "../model/CascadingDescriptor.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::presentation;

#include "../model/CompositeExecutionObject.h"
#include "../model/ApplicationExecutionObject.h"
#include "../model/ExecutionObject.h"
#include "../model/NodeNesting.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::model::components;

#include "../adaptation/context/RuleAdapter.h"
using namespace ::br::pucrio::telemidia::ginga::ncl::adaptation::context;

#include "../FormatterScheduler.h"
#include "ObjectCreationForbiddenException.h"

#include <map>
#include <vector>
#include <set>
#include <string>
using namespace std;

namespace br {
namespace pucrio {
namespace telemidia {
namespace ginga {
namespace ncl {
namespace emconverter {
  class FormatterConverter : public IEventListener {
	private:
		int depthLevel;
		map<string, ExecutionObject*>* executionObjects;
		set<ExecutionObject*>* settingObjects;
		void* linkCompiler; //FormatterLinkConverter*
		FormatterScheduler* scheduler;
		RuleAdapter* ruleAdapter;
		pthread_mutex_t objectsMutex;
		bool handling;

	public:
		FormatterConverter(RuleAdapter* ruleAdapter);
		virtual ~FormatterConverter();

		void stopListening(void* event);
		set<ExecutionObject*>* getRunningObjects();
		void setHandlingStatus(bool hanling);
		ExecutionObject* getObjectFromNodeId(string id);

		void setScheduler(FormatterScheduler* scheduler);
		void setDepthLevel(int level);
		int getDepthLevel();
		void checkGradSameInstance(
				set<ReferNode*>* gradSame, ExecutionObject* object);

		CompositeExecutionObject* addSameInstance(
			    ExecutionObject* executionObject,
			    ReferNode* referNode);

	private:
		void addExecutionObject(
			    ExecutionObject* executionObject,
			    CompositeExecutionObject* parentObject,
			    int depthLevel);

	public:
		void compileExecutionObjectLinks(
			    ExecutionObject* executionObject, int depthLevel);

		ExecutionObject* getExecutionObject(
			    NodeNesting* perspective,
			    GenericDescriptor* descriptor,
			    int depthLevel) throw(ObjectCreationForbiddenException*);

		set<ExecutionObject*>* getSettingNodeObjects();

	private:
		CompositeExecutionObject* getParentExecutionObject(
			    NodeNesting* perspective,
			    int depthLevel) throw(ObjectCreationForbiddenException*);

	public:
		FormatterEvent* getEvent(
			    ExecutionObject* executionObject,
			    InterfacePoint* interfacePoint,
			    int ncmEventType,
			    string key);

	private:
		void createMultichannelObject(
		    CompositeExecutionObject* compositeObject, int depthLevel);

		ExecutionObject* createExecutionObject(
			    string id,
			    NodeNesting* perspective,
			    CascadingDescriptor* descriptor,
			    int depthLevel);

	public:
		static CascadingDescriptor* getCascadingDescriptor(
			    NodeNesting* nodePerspective,
			    GenericDescriptor* descriptor);

		void compileExecutionObjectLinks(
			    ExecutionObject* executionObject,
			    Node* dataObject,
			    CompositeExecutionObject* parentObject,
			    int depthLevel);

	private:
		void setActionListener(LinkAction* action);

	public:
		ExecutionObject* processExecutionObjectSwitch(
			    ExecutionObjectSwitch* switchObject);

	private:
		void resolveSwitchEvents(
			    ExecutionObjectSwitch* switchObject, int depthLevel);

		FormatterEvent* insertNode(
			    NodeNesting* perspective,
			    InterfacePoint* interfacePoint,
			    GenericDescriptor* descriptor);

	public:
		FormatterEvent* insertContext(
			    NodeNesting* contextPerspective, Port* port);

		bool removeExecutionObject(
			    ExecutionObject* executionObject, ReferNode* referNode);

		bool removeExecutionObject(ExecutionObject* executionObject);
		ExecutionObject* hasExecutionObject(
			    Node* node, GenericDescriptor* descriptor);

		FormatterCausalLink* addCausalLink(
			    ContextNode* context, CausalLink* link);

		void eventStateChanged(
			    void* someEvent, short transition, short previousState);

		short getPriorityType();
		void reset();
  };
}
}
}
}
}
}

#endif /*FORMATTERCONVERTER_H_*/
