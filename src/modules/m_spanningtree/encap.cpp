/*
 * InspIRCd -- Internet Relay Chat Daemon
 *
 *   Copyright (C) 2008 Craig Edwards <craigedwards@brainbox.cc>
 *
 * This file is part of InspIRCd.  InspIRCd is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "inspircd.h"
#include "xline.h"

#include "m_spanningtree/treesocket.h"
#include "m_spanningtree/treeserver.h"
#include "m_spanningtree/utils.h"

/* $ModDep: m_spanningtree/utils.h m_spanningtree/treeserver.h m_spanningtree/treesocket.h */

bool TreeSocket::Encap(const std::string &prefix, std::deque<std::string> &params)
{
	if (params.size() > 1)
	{
		if (InspIRCd::Match(ServerInstance->Config->ServerName, params[0]))
		{
			Event event((char*) &params, (Module*)this->Utils->Creator, "encap_received");
			event.Send(ServerInstance);
		}
		
		params[params.size() - 1] = ":" + params[params.size() - 1];

		if (params[0].find_first_of("*?") != std::string::npos)
		{
			Utils->DoOneToAllButSender(prefix, "ENCAP", params, prefix);
		}
		else
			Utils->DoOneToOne(prefix, "ENCAP", params, params[0]);
	}
	return true;
}

