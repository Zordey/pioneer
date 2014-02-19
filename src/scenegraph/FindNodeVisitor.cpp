<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "FindNodeVisitor.h"
#include "Node.h"
#include "utils.h"

namespace SceneGraph {

FindNodeVisitor::FindNodeVisitor(Criteria c, const std::string &s)
: m_criteria(c)
, m_string(s)
{
}

void FindNodeVisitor::ApplyNode(Node &n)
{
	if (m_criteria == MATCH_NAME_STARTSWITH) {
		if (!n.GetName().empty() && starts_with(n.GetName(), m_string.c_str()))
			m_results.push_back(&n);
<<<<<<< HEAD
=======
	} else if (m_criteria == MATCH_NAME_ENDSWITH ) {
		if (!n.GetName().empty() && ends_with(n.GetName(), m_string.c_str()))
			m_results.push_back(&n);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	} else {
		if (!n.GetName().empty() && n.GetName() == m_string)
			m_results.push_back(&n);
	}

	n.Traverse(*this);
}

}
