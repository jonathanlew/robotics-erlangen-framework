/**************************************************************************
*   Copyright 2018 Andreas Wendler                                        *
*   Robotics Erlangen e.V.                                                *
*   http://www.robotics-erlangen.de/                                      *
*   info@robotics-erlangen.de                                             *
*                                                                         *
*   This program is free software: you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation, either version 3 of the License, or     *
*   any later version.                                                    *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
**************************************************************************/

import { amunFunctions } from "base/amun";
import * as debug from "base/debug";
import * as plot from "base/plot";

let startTimes: {[name: string]: number} = {};

export function start(name: string, robotId: number) {
	let key = `${name}.${robotId}`;
	if (startTimes[key]) {
		throw new Error("timing: multiple start calls");
	}

	startTimes[key] = amunFunctions.getCurrentTime();
}

export function finish(name: string, robotId: number) {
	let key = `${name}.${robotId}`;
	if (startTimes[key] == undefined) {
		throw new Error("timing: no start call");
	}

	let timeDiffMs = (amunFunctions.getCurrentTime() - startTimes[key]) * 1000;
	if (timeDiffMs < 0.001) {
		timeDiffMs = 0;
	}

	debug.push("Timing");
	debug.set(name, `${String(timeDiffMs).slice(0, 5)}  ms`);
	debug.pop();

	plot.addPlot(key, timeDiffMs);

	delete startTimes[key];
}