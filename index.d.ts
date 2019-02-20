declare module logicsim {

    function newBoard(id: string, boardObject: BoardObject): void;
    function startBoard(id: string, ticksToRun?: number): void;
    function stopBoard(id: string): void;
    function getBoardStatus(id: string): BoardStatus;
    function getBoard(id: string): BoardState;
    function triggerInput(id: string, indexToTrigger: number, inputIndex: number, state: 1 | 0): void;
}

declare type BoardObject = {
    links: number;
    threads: number;
    components: {
        type: Components;
        inputs: number[];
        outputs: number[];
    }[];
}

declare type BoardStatus = {
    currentSpeed: number;
    currentState: number;
    threadCount: number;
    componentCount: number;
    linkCount: number;
    tick: number;
}

declare type BoardState = {
    components: boolean[][];
    links: boolean[];
}


declare type Components = 'SWITCH' | 'XOR' | 'AND' | 'OR' | 'NOT' | 'BUTTON' | 'DELAY' | 'CLK';

export {logicsim, BoardState, BoardStatus, BoardObject};
